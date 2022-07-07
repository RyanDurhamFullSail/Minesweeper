#pragma once
#include "wx/wx.h"


class Window : public wxFrame
{
public:
	Window();
	~Window();

public:
	int minefieldX = 10;
	int minefieldY = 10;
	wxButton **field;
	int *mines = nullptr;
	bool firstClick = true;

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

