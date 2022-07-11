#pragma once
#include "DataCollector.h"
#include "Server.h"

class MessageHelper
{
private:
public:
	static void makeCorrectStructureOfText(Message&);
	static bool isCorrectUser(UserData &, Server*);
	static bool	isCorrectMessage(Message& );
};