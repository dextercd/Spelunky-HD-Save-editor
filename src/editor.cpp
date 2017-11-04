#include "editor.hpp"

editor::editor(save& s, const save& o, wxWindow* parent)
	: wxNotebook{parent, wxID_ANY}
	, sav{s}
	, original{o}
{
	add_range(layout.elements + 0,   4,  "Plays/wins");
	add_range(layout.elements + 4,   3,  "Deathmatch");
	add_range(layout.elements + 7,   3,  "Stats");
	add_range(layout.elements + 10,  8,  "Death");
	add_range(layout.elements + 18,  3,  "Shortcuts");
	add_range(layout.elements + 21,  10, "Places");
	add_range(layout.elements + 31,  56, "Creatures");
	add_range(layout.elements + 87,  34, "Items");
	add_range(layout.elements + 121, 14, "Traps");
	add_range(layout.elements + 135, 16, "Characters");
	add_range(layout.elements + 151, 56, "Kill count");
	add_range(layout.elements + 207, 56, "Killed by Monsters");
	add_range(layout.elements + 263, 14, "Killed by Traps");
	add_range(layout.elements + 277, 12, "Settings");
}

void editor::add_range(save_element* elements, std::size_t count, const char* name)
{
	auto tab = new wxScrolledWindow{this, wxID_ANY};
	auto tab_sizer = new wxBoxSizer{wxVERTICAL};
	tab->SetSizer(tab_sizer);
	
	for(std::size_t i{}; i != count; ++i) {
		std::visit([&, this](auto&& element) {
			auto input = new element_editor{element, tab, sav, original};
			tab_sizer->Add(input, 0, wxEXPAND);
			this->edit_elements.emplace_back(input);
		}, elements[i]);
	}

	tab->FitInside();
	tab->SetScrollRate(15, 15);

	AddPage(tab, name);

}

void editor::refresh()
{
	for(auto&& el : edit_elements) {
		el->refresh();
	}
}
