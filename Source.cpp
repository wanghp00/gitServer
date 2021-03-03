﻿#include "Server.h"

class Program {
private:
    ENetAddress address;
    Server m_Server;

public:
    void Start() {
        //m_Server = new Server();
        address.host = ENET_HOST_ANY;
        address.port = 8889;
        m_Server.Start(&address, address.port);
        //Console.WriteLine("{0} 开始监听...", ip);
        std::cout << "开始监听..." << std::endl;
    }
};

int main()
{
    Program p;
    p.Start();
    while (1);
    return 0;
}

//#include <iostream>
//#include <enet/enet.h>
//#include <string>
//#include <cstring>
//#include <map>
//#include <stdio.h>
//class ClientData
//{
//private:
//	int m_id;
//	std::string m_username;
//	ENetPeer* m_peer;
//
//public:
//	ClientData(int id) : m_id(id) {}
//
//	void SetUsername(std::string username) { m_username = username; }
//	void SetPeer(ENetPeer* p) { m_peer = p; }
//
//	int GetID() { return m_id; }
//	std::string GetUsername() { return m_username; }
//	ENetPeer* GetPeer() { return m_peer; }
//};
//
//std::map<int, ClientData*> client_map;
//
//void BroadcastPacket(ENetHost* server, const char* data)
//{
//	ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
//	enet_host_broadcast(server, 0, packet);
//}
//
//void SendPacket(ENetPeer* peer, const char* data)
//{
//	ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
//	enet_peer_send(peer, 0, packet);
//}
//
//void ParseData(ENetHost* server, int id, char* data)
//{
//
//	int data_type;
//	sscanf(data, "%d|", &data_type);
//
//	switch (data_type)
//	{
//	case 1:
//	{
//		char msg[80];
//		sscanf(data, "%*d|%[^\n]", &msg);
//
//		char send_data[1024] = { '\0' };
//		sprintf(send_data, "1|%d|%s", id, msg);
//		BroadcastPacket(server, send_data);
//		break;
//	}
//	case 2:
//	{
//		char username[80];
//		sscanf(data, "2|%[^\n]", &username);
//
//		char send_data[1024] = { '\0' };
//		sprintf(send_data, "2|%d|%s", id, username);
//
//		BroadcastPacket(server, send_data);
//		client_map[id]->SetUsername(username);
//
//		break;
//	}
//	}
//}
//
//int main(int argc, char** argv)
//{
//	if (enet_initialize() != 0)
//	{
//		fprintf(stderr, "An error occurred while initializing ENet.\n");
//		return EXIT_FAILURE;
//	}
//	atexit(enet_deinitialize);
//
//	ENetAddress address;
//	ENetHost* server;
//	ENetEvent event;
//
//	address.host = ENET_HOST_ANY;
//	address.port = 1234;
//
//	server = enet_host_create(&address, 64, 0, 0, 0);
//
//	if (server == NULL)
//	{
//		fprintf(stderr, "An error occurred while trying to create an ENet server host!\n");
//		return EXIT_FAILURE;
//	}
//
//	// GAME LOOP START
//	int new_player_id = 0; // An auto incrementing variable to give to any new clients
//	while (true)
//	{
//		while (enet_host_service(server, &event, 1000) > 0)
//		{
//
//			switch (event.type)
//			{
//			case ENET_EVENT_TYPE_CONNECT:
//			{
//				printf("A new client connected from %x:%u.\n",
//					event.peer->address.host,
//					event.peer->address.port);
//				puts("connected");
//				for (auto const& x : client_map)
//				{
//					char send_data[1024] = { '\0' };
//					sprintf(send_data, "2|%d|%s", x.first, x.second->GetUsername().c_str());
//					//BroadcastPacket(server, send_data);
//				}
//
//				// Increment new_player_id with each new connection
//				new_player_id++;
//				client_map[new_player_id] = new ClientData(new_player_id);
//				event.peer->data = client_map[new_player_id];
//				client_map[new_player_id]->SetPeer(event.peer);
//
//				char data_to_send[126] = { '\0' };
//				sprintf(data_to_send, "3|%d", new_player_id);
//				SendPacket(event.peer, data_to_send);
//
//				break;
//			}
//			case ENET_EVENT_TYPE_RECEIVE:
//			{
//				printf("A packet of length %u containing %s was received from %x:%u on channel %u.\n",
//					event.packet->dataLength,
//					event.packet->data,
//					event.peer->address.host,
//					event.peer->address.port,
//					event.channelID);
//				puts("recv");
//				ParseData(server, static_cast<ClientData*>(event.peer->data)->GetID(), (char*)event.packet->data);
//				enet_packet_destroy(event.packet);
//				break;
//			}
//			case ENET_EVENT_TYPE_DISCONNECT:
//			{
//				printf("%x:%u disconnected.\n",
//					event.peer->address.host,
//					event.peer->address.port);
//
//				char disconnected_data[126] = { '\0' };
//				sprintf(disconnected_data, "4|%d", static_cast<ClientData*>(event.peer->data)->GetID());
//				BroadcastPacket(server, disconnected_data);
//
//				event.peer->data = NULL;
//				break;
//			}
//			}
//		}
//
//	}
//	// GAME LOOP END
//
//	enet_host_destroy(server);
//
//	return EXIT_SUCCESS;
//}
