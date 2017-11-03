#ifndef SPELUNKY_EDITOR_HPP
#define SPELUNKY_EDITOR_HPP

#include <vector>

#include <wx/wx.h>

#include "save.hpp"
#include "element_editor.hpp"

class editor : public wxScrolledWindow
{
	save& sav;
	const save& original;
	save_layout layout;

	wxBoxSizer* sizer;
	std::vector<element_editor*> edit_elements;

public:
	editor(save& s, const save& o, wxWindow* parent);
	void refresh();
};

#endif // SPELUNKY_EDITOR_HPP
