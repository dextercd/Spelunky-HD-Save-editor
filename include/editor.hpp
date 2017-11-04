#ifndef SPELUNKY_EDITOR_HPP
#define SPELUNKY_EDITOR_HPP

#include <vector>

#include <wx/wx.h>
#include <wx/notebook.h>

#include "save.hpp"
#include "element_editor.hpp"

class editor : public wxNotebook
{
	save& sav;
	const save& original;
	save_layout layout;

	std::vector<element_editor*> edit_elements;
	void add_range(save_element* elements, std::size_t count, const char* name);

public:
	editor(save& s, const save& o, wxWindow* parent);
	void refresh();
};

#endif // SPELUNKY_EDITOR_HPP
