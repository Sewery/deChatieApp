#pragma once
#include "DataCollector.h"
class Server 
{
    private:
        const int Host= ENET_HOST_ANY;
        const int Port=1234;
        const int  Max_Connections = 32;
        ENetAddress address;
        ENetHost * host;
        ENetEvent event;
        std::vector<ENetPeer*> peers;
        
    public:
        std::map<int, UserData> getUserByAddress;
        Server();
        bool init();
        void closeServer();
        void sendPacket(enet_uint8* data, ENetPeer* peer);
        void broadcastPacketUser(enet_uint8* data);
        void broadcastPacketMessage(enet_uint8* data);
        void serverEventsHandling();
};