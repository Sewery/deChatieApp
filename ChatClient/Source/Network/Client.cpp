#include "..\Network\Client.h"
#include "..\Util\Timer.h"
#include "..\ResourceController\MessageHelper.h"
#include "..\Gui\Window.h" 
Client::Client()
{
	init();
}

static void receiveData(Client& client)
{
	while (true)
	{
		while (enet_host_service(client.getClientHost(), &client.getEvent(), 0) > 0)
		{

			switch (client.getEvent().type)
			{
				case ENET_EVENT_TYPE_RECEIVE:
				{
					if (client.getEvent().packet->dataLength == sizeof(UserData))
					{		
						
						UserData * newUser = static_cast<UserData*>(static_cast<void*>(client.getEvent().packet->data));
						LOG("Recevied userdata of " << newUser->nick);
						DataCollector::addUser(*newUser);

					}
					else if (client.getEvent().packet->dataLength == sizeof(Message))
					{
						Message * newMess = static_cast<Message*>(static_cast<void*>(client.getEvent().packet->data));
						LOG("Recevied message from" << newMess->user.nick<<" of " << newMess->messLineTexture->textLength<<" length");
						DataCollector::addMessage(*newMess);
					}

					break;
				}

			}
		}
	}


}
bool Client::init()
{
	clientHost= enet_host_create(nullptr, 1, 1, 0, 0);

	if (getClientHost() == nullptr)
	{
		LOG_ERROR("An error occurred while trying to create an ENet client host!");
		return false;
	}
	return true;
}

bool Client::connectWithServer()
{

	enet_address_set_host(&enetAddress, Address);
	enetAddress.port = Port;

	peer = enet_host_connect(getClientHost(), &enetAddress, 1, 0);
	if (peer == NULL)
	{
		LOG_ERROR("No available peers for initiating an ENet connection!");
		return false;
	}
	if (enet_host_service(getClientHost(), &event, FIVE_SEC_IN_MS) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		LOG("Connection to "<<Address<<" succeeded.");
	}
	else
	{
		enet_peer_reset(peer);
		LOG("Connection to "<<Address<<" failed.");
		return false;
	}
	return true;

}
bool Client::connectionRequest(UserData user,std::thread & threadRecData,std::string& info)
{
	int numOfUsers = DataCollector::getNumberOfUsers();
	if (!connectWithServer())
	{
		info = Commands::Not_Possible_Connect_Statement ;
		return isConnected = false;
	}
	threadRecData=std::thread(&receiveData,std::ref( * this));
	sendPacketUser(static_cast<enet_uint8*>(static_cast<void*>(&user)));
	Timer timer;
	timer.start();
	while (timer.getTicks() <= FIVE_SEC_IN_MS)//Waiting for receving back user info
	{
		int currNumOfUsers = DataCollector::getNumberOfUsers();
		bool isAccepted = false;
		if (currNumOfUsers > numOfUsers)
		{
			while (currNumOfUsers != numOfUsers)
			{
				if (!strcmp(user.nick, DataCollector::chatUsers[currNumOfUsers - 1].nick))
				{
					user = DataCollector::chatUsers[currNumOfUsers-1];
					return isConnected = true;
				}
				numOfUsers++;
			}
		}	
	}
	info = Commands::Bad_Nick_Statement;
	LOG_ERROR("Didn't recevied back userdata.");
	return isConnected=false;
}
void  Client::sendPacketMessage(enet_uint8* data)
{
	ENetPacket* packet = enet_packet_create(data, sizeof(Message), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}
void  Client::sendPacketUser(enet_uint8* data)
{
	ENetPacket* packet = enet_packet_create(data, sizeof(UserData), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}
void Client::disconnectWithServer()
{
	enet_peer_disconnect(peer, 0);

	while (enet_host_service(clientHost, &event, THREE_SEC_IN_MS) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			enet_packet_destroy(event.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			LOG("Disconnection succeeded.");
			break;
		}
	}
}
void Client::sendMessage(char * input,UserData user, std::shared_ptr<Window> window)
{
	Message mess = MessageHelper::createMessage(input, user, window.get());
	sendPacketMessage(static_cast<enet_uint8*>(static_cast<void*>(&mess)));
}
