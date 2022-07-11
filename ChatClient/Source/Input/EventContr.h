#pragma once
#include "..\Util\Config.h"
class EventContr
{
private:
	const int Acceleration_Factor = 20;
public:
	bool scrolling = true;
	int scrollVel = 0;
	bool handleEvents(std::string&,SDL_Event &,bool&);
};