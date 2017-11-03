#include "element_editor.hpp"

void element_editor::setup_label(wxWindow* parent, const char* description)
{
	label = new wxStaticText{parent, wxID_ANY, description}; 
	Add(label, 0, wxALIGN_CENTER);
}

void element_editor::setup_revert(wxWindow* parent)
{
	revert_button = new wxButton{parent, wxID_ANY, "revert"};
	parent->Bind(wxEVT_BUTTON, &element_editor::revert_event, this, revert_button->GetId());
	Add(revert_button, 0, wxALIGN_CENTER);
	update_revert_button();
}

void element_editor::update_revert_button()
{
	revert_button->Enable(input->is_changed());
}

void element_editor::refresh()
{
	input->update_input_widget();
	update_revert_button();
}

void element_editor::edited_event(wxCommandEvent& event)
{
	update_revert_button();
}

void element_editor::revert_event(wxCommandEvent& event)
{
	input->reset();
	input->update_input_widget();
	update_revert_button();
}
