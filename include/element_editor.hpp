#ifndef SPELUNK_ELEMENT_EDITOR
#define SPELUNK_ELEMENT_EDITOR

#include <wx/wx.h>

#include "input_element.hpp"
#include "events.hpp"

class element_editor : public wxBoxSizer
{
	wxStaticText* label = nullptr;
	wxButton* revert_button = nullptr;

	input_element_base* input;

	save& sav;
	const save& original;

	void setup_label(wxWindow* parent, const char* description);

	template<class value_type>
	void setup_input(wxWindow* parent, value_type& value_element);

	void setup_revert(wxWindow* parent);

	void update_revert_button();;

	void edited_event(wxCommandEvent& event);
	void revert_event(wxCommandEvent& event);

public:
	template<class value_type>
	element_editor(value_type& val_element, wxWindow* parent, save& s, const save& o);

	void refresh();
};

#include "element_editor.inl"

#endif // SPELUNKY_ELEMENT_EDITOR
