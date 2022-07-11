#pragma once
#include "..\Gui\WinCompsData.h"
#include "..\ResourceController\DataCollector.h"
class MessageHelper
{
private:
public:
	static void givePositionForNewMessage(Message&);
	static void makeCorrectStructureOfText(Message&);
	static Message createMessage( char* , UserData , WinCompsData *  );
};