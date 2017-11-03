#ifndef SPELUNK_EVENTS_HPP
#define SPELUNK_EVENTS_HPP

enum events
{
	open_file = 1,
	save_file,
};

wxDECLARE_EVENT(SP_EDITED, wxCommandEvent);

#endif
