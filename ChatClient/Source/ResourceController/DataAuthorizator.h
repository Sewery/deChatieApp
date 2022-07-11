#pragma once
#include "../ResourceController/DataCollector.h"

class DataAuthorizator
{
public:
	static bool checkInputNick(std::string);
	static bool	checkInputMessage(std::string, UserData);
};