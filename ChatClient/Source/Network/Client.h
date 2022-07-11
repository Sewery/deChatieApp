#pragma once
#include "..\ResourceController\DataCollector.h"
class Window;
class Client
{
private:
	const int Wainting_Time_For_Connection = 5000;
	const char* Address = "127.0.0.1";//localhost
	const int Port = 1234;
	ENetHost* clientHost;
	ENetAddress enetAddress;
	ENetEvent event;
	ENetPeer* peer;
	bool connectWithServer();
	void sendPacketMessage(enet_uint8*);
	void sendPacketUser(enet_uint8*);
	bool init();
	
public:
	Client();
	~Client(){};
	bool isConnected = false;
	bool connectionRequest(UserData, std::thread&,std::string&);
	void sendMessage(char *, UserData, std::shared_ptr<Window>);
	void disconnectWithServer();
	ENetHost* getClientHost() { return clientHost; }
	ENetEvent& getEvent() { return event; }
};

