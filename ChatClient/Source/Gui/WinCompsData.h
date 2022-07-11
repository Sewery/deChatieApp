#pragma once
#include "..\Util\Data.h"

class WinCompsData
{
public:
	//Size of screen
	static  const int SCREEN_WIDTH = 1000;
	static  const int SCREEN_HEIGHT = 800;
	const Color Main_Background_Color = Color::slategrey;
protected:

	WinCompsData(){};
	~WinCompsData() {};
	//Sdl Components
	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

	//Textures
	std::array<TextTexture, 5> infoTextTexture;
	const std::unordered_map<std::string, int> iTextTPos =
	{
		{Commands::Entry_Statement,0},
		{Commands::Bad_Nick_Statement,1},
		{Commands::Lost_Connection_Statement,2},
		{Commands::Info_After_Connection,3},
		{Commands::Not_Possible_Connect_Statement,4}

	};
	TextTexture inputTextTexture[InputProperties::Max_Lines]={};

};