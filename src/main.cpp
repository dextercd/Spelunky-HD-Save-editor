#include <array>
#include <iostream>
#include <variant>
#include <fstream>
#include <vector>
#include <string>

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include "editor.hpp"
#include "events.hpp"

using namespace std::literals;

wxDEFINE_EVENT(SP_EDITED, wxCommandEvent);

class motherframe : public wxFrame {
	wxMenu* menu_file = nullptr;
	wxMenuBar* menu_bar = nullptr;
	wxStatusBar* status_bar = nullptr;
	editor* edit = nullptr;

	save current_save;
	save original_save;

	void setup_menu()
	{
		menu_file = new wxMenu;
		menu_file->Append(
			events::open_file,
			"&Open save..\tCtrl-O",
			"Open a save file to edit."
		);

		menu_file->Append(
			events::save_file,
			"&Save to file..\tCtrl-S",
			"Store the current save."
		);

		menu_bar = new wxMenuBar;
		menu_bar->Append(menu_file, "&File");

		SetMenuBar(menu_bar);
	}

	void on_close(wxCloseEvent& event)
	{
		if(current_save != original_save) {
			auto result = wxMessageBox(
				"Current changes have not been saved, save changes?",
				"Please confirm",
				wxICON_QUESTION | wxYES_NO | wxYES_DEFAULT,
				this
			);

			if(result == wxYES) {
				save_file();
				// operation canceled, we don't want to close now.
				if(current_save != original_save && event.CanVeto()) {
					event.Veto();
					return;
				}
			}
		}

		Destroy();
	}

	void setup_status_bar()
	{
		status_bar = CreateStatusBar();
	}

	void setup_editor()
	{
		edit = new editor{current_save, original_save, this};
	}

public:
	motherframe()
		: wxFrame{
			NULL,
			wxID_ANY,
			"Spelunky save editor.",
			wxDefaultPosition,
			wxSize{720, 480}
		}
	{
		setup_menu();
		setup_status_bar();
		setup_editor();
	}

	void open_file(wxCommandEvent& event)
	{
		if(current_save != original_save) {
			auto result = wxMessageBox(
				"Current changes have not been saved, discard?",
				"Please confirm",
				wxICON_QUESTION | wxYES_NO | wxNO_DEFAULT,
				this
			);

			if(result != wxYES)
				return;
		}

		wxFileDialog file_dialog{
			this,
			"Open Spelunky save file",
			"",
			"",
			"Spelunky save file (*.sav)|*.sav",
			wxFD_OPEN | wxFD_FILE_MUST_EXIST
		};

		auto result = file_dialog.ShowModal();
		if(result == wxID_CANCEL)
			return;
		
		read_save(original_save, file_dialog.GetPath().ToStdString());
		current_save = original_save;
		edit->refresh();
	}

	void save_file_event(wxCommandEvent& event)
	{
		save_file();
	}

	void save_file()
	{
		wxFileDialog file_dialog{
			this,
			"Save to file.",
			"",
			"",
			"Spelunky save file (*.sav)|*.sav",
			wxFD_SAVE
		};

		auto result = file_dialog.ShowModal();
		if(result == wxID_CANCEL)
			return;
		
		write_save(current_save, file_dialog.GetPath().ToStdString());

		original_save = current_save;
		edit->refresh();
	}

private:
	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(motherframe, wxFrame)
	EVT_MENU(events::open_file, motherframe::open_file)
	EVT_MENU(events::save_file, motherframe::save_file_event)
	EVT_CLOSE(motherframe::on_close)
wxEND_EVENT_TABLE()


class save_editor : public wxApp {
	wxFrame* frame = nullptr;
public:
	bool OnInit() override;
};


bool save_editor::OnInit()
{
	frame = new motherframe;
	frame->Show();
	return true;
}

wxIMPLEMENT_APP(save_editor);
