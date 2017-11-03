#ifndef SPELUNK_INPUT_ELEMENT_HPP
#define SPELUNK_INPUT_ELEMENT_HPP

#include <wx/wx.h>
#include <wx/spinctrl.h>

#include "save.hpp"
#include "events.hpp"

inline static void send_edited_event(wxWindow* w)
{
	wxCommandEvent event{SP_EDITED, w->GetId()};
	w->ProcessWindowEvent(event);
}

class input_element_base
{
public:
	virtual void reset() =0;
	virtual void update_input_widget()=0;
	virtual bool is_changed() const=0;
};

template<class T>
class input_element;

template<>
class input_element<int_value> : public wxSpinCtrl, public input_element_base
{
	int_value& value_element;
	save& current_save;
	const save& original_save;

	void handle_input(wxSpinEvent& event)
	{
		value_element.set_value(current_save, GetValue());
		send_edited_event(this);
	}

public:
	input_element(wxWindow* parent, int_value& value_element, save& current_save, const save& original_save)
		: wxSpinCtrl{parent, wxID_ANY}
		, value_element{value_element}
		, current_save{current_save}
		, original_save{original_save}
	{
		SetRange(std::numeric_limits<std::int32_t>::min(), std::numeric_limits<std::int32_t>::max());
		Bind(wxEVT_SPINCTRL, &input_element::handle_input, this);
		update_input_widget();
	}

	void update_input_widget() override
	{
		SetValue(value_element.get_value(current_save));
	}

	void reset() override
	{
		value_element.set_value(current_save, value_element.get_value(original_save));
	}

	bool is_changed() const override
	{
		return value_element.get_value(current_save) != value_element.get_value(original_save);
	}
};

template<>
class input_element<bool_value> : public wxCheckBox, public input_element_base
{
	bool_value& value_element;
	save& current_save;
	const save& original_save;

	void handle_input(wxCommandEvent& event)
	{
		value_element.set_value(current_save, GetValue());
		send_edited_event(this);
	}


public:
	input_element(wxWindow* parent, bool_value& value_element, save& current_save, const save& original_save)
		: wxCheckBox{parent, wxID_ANY, wxEmptyString}
		, value_element{value_element}
		, current_save{current_save}
		, original_save{original_save}
	{
		Bind(wxEVT_CHECKBOX, &input_element::handle_input, this);
		update_input_widget();
	}

	void update_input_widget() override
	{
		SetValue(value_element.get_value(current_save));
	}

	void reset() override
	{
		value_element.set_value(current_save, value_element.get_value(original_save));
	}

	bool is_changed() const override
	{
		return value_element.get_value(current_save) != value_element.get_value(original_save);
	}
};

#endif // SPELUNK_INPUT_ELEMENT_HPP
