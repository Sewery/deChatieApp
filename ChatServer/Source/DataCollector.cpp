#include "DataCollector.h"
 int DataCollector::userCounter = 0;
 int DataCollector::messageCounter = 0;
 UserData DataCollector::chatUsers[TextContentProperties::Max_Users] = {};
 Message DataCollector::chatContent[TextContentProperties::Max_Messages] = {};
void DataCollector::addMessage(Message& mess)
{
	mess.id = messageCounter;
	chatContent[messageCounter++] = mess;
}
void  DataCollector::addUser(UserData& user)
{
	user.id = userCounter;
	chatUsers[userCounter++] = user;
}

void DataCollector::removeUser(UserData user)
{
	chatUsers[user.id] = UserData();
}
