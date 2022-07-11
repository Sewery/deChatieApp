#pragma once
#include "..\Gui\WinCompsContr.h"


class Window : public WinCompsContr
{
private:
	const char* Title_Of_Window = "Chatter";
	bool initWindow();
public:
	Window();
	~Window();

	void loadMediaAndSetUp();
	void renderMessages();
	void renderInput();
	void renderInfo(const char*);
	void renderBackground();
	void cleanScreen();
	void cleanInput( char*);
	void renderSDL(){ SDL_RenderPresent(pRenderer); }
	void changeInput(const char* str);
};