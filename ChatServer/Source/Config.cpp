#include "Config.h"
#pragma warning(disable : 4996)//
void copyCString(char* destination,const  char* source)
{

	if (source == "")
		memset(destination, 0, sizeof(destination));
	else
		strcpy(destination,  source);
}