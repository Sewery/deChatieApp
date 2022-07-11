#pragma once
#include "..\Util\Data.h"

class DataCollector
{
private:
	static int userCounter ;
	static int messageCounter ;
public:
	static UserData chatUsers[TextContentProperties::Max_Users];
	static Message chatContent[TextContentProperties::Max_Messages];
	static bool loadedMessages[TextContentProperties::Max_Messages];
	static void addMessage(Message & );
	static void addUser(UserData &);
	static void removeUser(UserData );
	static int getNumberOfMesseages(){ return messageCounter; }
	static int getNumberOfUsers() { return userCounter; }

};