#pragma once
#include "wx/wx.h"

class Window;

class Minesweeper : public wxApp
{

	Window* window = nullptr;

public:
	virtual bool OnInit();
};

