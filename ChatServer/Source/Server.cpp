#include "Server.h"
#include "Timer.h"
#include "MessageHelper.h"

Server::Server()
{
}

bool Server::init()
{
	address.host = Host;
	address.port = Port;

	host = enet_host_create(&address, Max_Connections, 1, 0, 0);

	if (host == nullptr)
	{
		LOG_ERROR("An error occurred while trying to create an ENet server host!");
		return true;
	}

	LOG("ENet server host iniitializated! ");
	return false;
}

void Server::closeServer()
{
	LOG("Turning off server...");
	enet_host_destroy(host);
}

void  Server::sendPacket(enet_uint8* data, ENetPeer* peer)
{
	ENetPacket* packet = enet_packet_create(data, sizeof(data), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
}

void Server::broadcastPacketUser(enet_uint8* data)
{
	ENetPacket* packet = enet_packet_create(data, sizeof(UserData), ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(host, 0, packet);
}
void Server::broadcastPacketMessage(enet_uint8* data)
{;
	ENetPacket* packet = enet_packet_create(data, sizeof(Message), ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(host, 0, packet);
}
void Server::serverEventsHandling()
{
	while (enet_host_service(host, &event, SECOND_IN_MS / TICKRATE) > 0)
	{
		switch (event.type)
		{

			case ENET_EVENT_TYPE_CONNECT:
			{
				LOG("A new client connected from " << event.peer->address.host << ":"<<event.peer->address.port );
				peers.push_back(event.peer);
				break;
			}
			case ENET_EVENT_TYPE_RECEIVE:
			{	
				
				if (event.packet->dataLength == sizeof(UserData))
				{
					LOG("User data recevied ");
					UserData* newUser = static_cast<UserData*>(static_cast<void*>(event.packet->data));
					if (MessageHelper::isCorrectUser(*newUser,this))
					{
						newUser->ipAddress = event.peer->address.host;
						DataCollector::addUser(*newUser);
						getUserByAddress[event.peer->address.host] = *newUser;
						LOG("Broadcasting data user of " << newUser->nick);
						broadcastPacketUser(event.packet->data);
					}
				}
				else if (event.packet->dataLength == sizeof(Message))
				{
		
					Message* newMess = static_cast<Message*>(static_cast<void*>(event.packet->data));
					if (MessageHelper::isCorrectMessage(*newMess))
					{
						DataCollector::addMessage(*newMess);
						LOG("Broadcasting data message of id:" << newMess->id);
						broadcastPacketMessage(event.packet->data);
					}
				}
				enet_packet_destroy(event.packet);
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
			{
				LOG(event.peer->address.host << ":" << event.peer->address.port << " disconnected.");

				DataCollector::removeUser(getUserByAddress[event.peer->address.host]);
				event.peer->data = nullptr;
				break;
			}

		}
	}
}


