#include "..\Util\Config.h"

std::time_t*  getTime()
{
	auto end = std::chrono::system_clock::now();
	std::time_t tek = std::chrono::system_clock::to_time_t(end);
	return &tek;

}

#pragma warning(disable : 4996)//
void copyCString(char* destination,const  char* source)
{

	if (source == "")
		memset(destination, 0, sizeof(destination));
	else
		strcpy(destination,  source);
}