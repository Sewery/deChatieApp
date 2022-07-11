#include "MessageHelper.h"



bool MessageHelper::isCorrectUser(UserData &user, Server* client)
{
	if (client->getUserByAddress[user.ipAddress].nick == user.nick) {
		return false;
	}
	return true; //strlen(user.nick) > 2 && strlen(user.nick) <= TextContentProperties::Max_Characters_Nick ? true : false;
}
bool MessageHelper::isCorrectMessage(Message & mess)
{
	bool correct = true;
	//for (auto line : mess.messLineTexture)
//	{
	//	if (strlen(line.text) > 4 && strlen(line.text) <= TextContentProperties::Max_Characters_Line)
	//		correct = false;
	//}
	return correct;
}
