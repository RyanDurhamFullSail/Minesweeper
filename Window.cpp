#include "Window.h"

wxBEGIN_EVENT_TABLE(Window, wxFrame)
wxEND_EVENT_TABLE()

Window::Window() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(500, 500), wxSize(500, 500))
{
	//Generate buttons for the field
	field = new wxButton * [minefieldX * minefieldY];

	//Create grid sizer for modular button placement
	wxGridSizer *minefield = new wxGridSizer(minefieldX, minefieldY, 0, 0);

	//Generate empty Mines
	mines = new int[minefieldX * minefieldY];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	//Populate Minefield with buttons
	for(int x = 0; x < minefieldX; x++)
	{
		for(int y = 0; y < minefieldY; y++)
		{
			//Create button and generate id based on location
			field[y * minefieldX + x] = new wxButton(this, 10000 + (y * minefieldX + x));
			field[y * minefieldX + x]->SetFont(font);
			minefield->Add(field[y * minefieldX + x], 1, wxEXPAND | wxALL);

			//Bind on lick event for all buttons in the field
			field[y * minefieldX + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Window::OnButtonClicked, this);

			//Set all mines to 0
			mines[y * minefieldX + x] = 0;
		}
	}

	this->SetSizer(minefield);
	minefield->Layout();
}

Window::~Window()
{
	delete[] mines;
	delete[] field;
}

void Window::OnButtonClicked(wxCommandEvent &evt)
{
	//Get x and y cord of clicked button
	int x = (evt.GetId() - 10000) % minefieldX;
	int y = (evt.GetId() - 10000) / minefieldX;

	// Generate Mines on first click
	if(firstClick)
	{
		int totalMines = 30;

		while (totalMines)
		{
			//Random x and y cord
			int rx = rand() % minefieldX;
			int ry = rand() % minefieldY;

			if (mines[ry * minefieldX + rx] == 0 && rx != x && ry != y)
			{
				mines[ry * minefieldX + rx] = -1;
				totalMines--;
			}
		}

		firstClick = false;
	}

	//Disable button after clicking it
	field[y * minefieldX + x]->Enable(false);

	//Check if player hit mine
	if(mines[y * minefieldX + x] == -1)
	{
		wxMessageBox("BOOOM! - Game Over :(");

		//Reset Game
		firstClick = true;
		for (int x = 0; x < minefieldX; x++)
		{
			for (int y = 0; y < minefieldY; y++)
			{
				mines[y * minefieldX + x] = 0;
				field[y * minefieldX + x]->SetLabel("");
				field[y * minefieldX + x]->Enable(true); 
				field[y * minefieldX + x]->SetOwnForegroundColour(*wxBLACK);
			}
		}
	}
	else
	{
		//Count Neighbors
		int neighborCount = 0;
		for(int i = -2; i < 2; i++)
		{
			for (int j = -2; j < 2; j++)
			{
				if(x+ i >= 0 && x+ i < minefieldX && y + j >= 0 && y + j < minefieldY)
				{
					if(mines[(y + j) * minefieldX + (x+ i)] == -1)
					{
						neighborCount++;
					}
				}
			}
		}
		switch(neighborCount)
		{
		case 1:
			field[y * minefieldX + x]->SetOwnForegroundColour(*wxBLUE);
		case 2:
			field[y * minefieldX + x]->SetOwnForegroundColour(*wxGREEN);
		case 3:
			field[y * minefieldX + x]->SetOwnForegroundColour(*wxRED);
		case 4:
			field[y * minefieldX + x]->SetOwnForegroundColour(*wxWHITE);
		case 5:
			field[y * minefieldX + x]->SetOwnForegroundColour(*wxYELLOW);
		case 6:
			field[y * minefieldX + x]->SetOwnForegroundColour(*wxCYAN);
		case 7:
			field[y * minefieldX + x]->SetOwnForegroundColour(*wxBLACK);
		case 8:
			field[y * minefieldX + x]->SetOwnForegroundColour(*wxLIGHT_GREY);
		}


		field[y * minefieldX + x]->SetLabel(std::to_string(neighborCount));
	}

	evt.Skip();
}