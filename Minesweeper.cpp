#include "Minesweeper.h"
#include "Window.h"

wxIMPLEMENT_APP(Minesweeper);

bool Minesweeper::OnInit()
{
	window = new Window();
	window->Show();
	return true;
}
