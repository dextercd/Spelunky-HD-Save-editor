#include "editor.hpp"

editor::editor(save& s, const save& o, wxWindow* parent)
	: wxScrolledWindow{parent, wxID_ANY}
	, sav{s}
	, original{o}
	, sizer{new wxBoxSizer{wxVERTICAL}}
{
	for(auto&& element : layout.elements) {
		std::visit([&](auto&& e) {
			auto el = new element_editor{e, this, sav, original};
			sizer->Add(el, 0, wxEXPAND);
			edit_elements.emplace_back(el);
		}, element);
	}

	SetSizer(sizer);
	FitInside();
	SetScrollRate(15, 15);
}

void editor::refresh()
{
	for(auto&& el : edit_elements) {
		el->refresh();
	}
}
