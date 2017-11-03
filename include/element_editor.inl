#include "element_editor.hpp"

template<class value_type>
element_editor::element_editor(value_type& val_element, wxWindow* parent, save& s, const save& o)
	: wxBoxSizer{wxHORIZONTAL}
	, sav{s}
	, original{o}
{
	setup_label(parent, val_element.description);
	AddStretchSpacer();
	setup_input(parent, val_element);
	setup_revert(parent);
}

template<class value_type>
void element_editor::setup_input(wxWindow* parent, value_type& value_element)
{
	auto i = new input_element<value_type>(parent, value_element, sav, original); 
	Add(i, 0);
	input = i;
	parent->Bind(SP_EDITED, &element_editor::edited_event, this, i->GetId());
}
