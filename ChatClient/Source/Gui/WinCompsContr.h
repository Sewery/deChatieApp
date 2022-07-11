#pragma once
#include "..\Gui\WinCompsData.h"
#include "..\ResourceController\DataCollector.h"

class WinCompsContr :public WinCompsData
{
public:
	void shiftUpDownMessages(int y);
	void messageViewRegulation();
protected:
	int currWindowWidth= SCREEN_WIDTH;
	int currWindowHeight= SCREEN_HEIGHT;
	DataCollector dataCollector;

	WinCompsContr();
	~WinCompsContr(){}
	void setUpInfoTextTexture();
	void setUpInputTextTexture();

	
	void loadMediaInfo();
	void loadMediaInput();
	void loadMediaServer();

};