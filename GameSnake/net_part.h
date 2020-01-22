#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define addr_len int                    //
#include <winsock2.h>                   // Windows
#include <windows.h>                    //  socket
#pragma comment(lib, "Ws2_32.lib")      //

#include <thread>
#include<functional>
#include <string>
#include <iostream>
#include <fstream>
#include <string.h> // memcpy
#include <map>
#include <chrono>

#include <math.h>

#include <vector>
#include <set>
#include <atomic>

#include <iphlpapi.h>
#include "Game.h"
#include "Painter.h"
#pragma comment(lib, "IPHLPAPI.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#define TIMEOUT 1

namespace net_utils {
	SOCKET make_socket(UINT16 port) {
		SOCKADDR_IN address;
		SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);   //
		if (sock < 0) {                                   // Create socket with
			std::cout << "Can't create socket" << std::endl; //     datagram-based protocol
			exit(1);                                         //
		}                                                    //

		address.sin_family = AF_INET;				//
		address.sin_port = htons(port);		// Create local address
		address.sin_addr.s_addr = INADDR_ANY;		//

		if (bind(sock, (sockaddr*)&address, sizeof(address)) == 0)	//
			std::cout << "Bind socket" << std::endl;					//
		else {															// Bind socket to
			std::cerr << "Can't bind socket" << std::endl;				//     client address
			exit(1);													//
		}																//

		int tv = 1 * 1000;  // user timeout in milliseconds [ms]                  
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));		// Set socket timeout
		return sock;
	}
	ULONG get_local_address() {
		char HostName[1024]; //создаем буфер для имени хоста
		if (!gethostname(HostName, 1024)) {//получаем имя хоста
			LPHOSTENT lphost = gethostbyname(HostName);
			return (*(in_addr*)(lphost->h_addr_list[0])).S_un.S_addr;
		}
	}
	void get_broadcast_address(SOCKET sock, SOCKADDR_IN& addr, UINT16 port) {
		addr.sin_family = AF_INET;					// Create broadcast
		addr.sin_port = htons(port);				//       address
		char broadcastEnable = '1';
		if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST,
			&broadcastEnable, sizeof(broadcastEnable)) == 0) {
			std::cout << "Got access to broadcast" << std::endl;
		}
		else {
			std::cerr << "Cant't get access to broadcast" << std::endl;
			exit(1);
		}
		addr.sin_addr.s_addr = INADDR_BROADCAST;

	}
}

class multiplayer {
private:
	UINT16 transive_port=33333, 
		recieve_port= 33334;
	SOCKET trans_sock,
		recieve_sock;
	ULONG server_address;
	SOCKADDR_IN broadcast_addr;
	std::vector<ULONG> players_addresses;
	bool wait_for_players = true,
		is_play = false;
	char buffer[1024];
	Game *game;

public:
	multiplayer(Game *game) {
		this->game = game;
		WSADATA wsaData;                        //     init of the Winsock DLL
		WSAStartup(0x0202, &wsaData);        // 
		trans_sock = net_utils::make_socket(transive_port);
		recieve_sock = net_utils::make_socket(recieve_port);
		net_utils::get_broadcast_address(trans_sock, broadcast_addr, transive_port);
		server_address = net_utils::get_local_address();
		players_addresses.push_back(0xFFFFFFFF);
		this->game->addNewPlayer(Player(Point2d(2, 0), Point2d(0, 1)));
	}
	void wait_for_players(std::string servername, unsigned short map_width, unsigned short map_height,unsigned char num_of_players) {
		while (wait_for_players)
			if (auto length = recv(recieve_sock, buffer, 1024, 0) > 0) {
				if (strcmp(buffer, "WANA_PLAY") == 0) {
					//команда, ip сервера, количество подключенных игроков, длина имени сервера, имя сервера
					int lenght = sprintf(buffer, "IM_SERVER%lu%c%hu%s", server_address, players_addresses.size(), servername.size(), servername.c_str());
					sendto(trans_sock, buffer, lenght, 0, (sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
				}
				if (memcmp(buffer, "IM_PLAY",7) == 0) {
					players_addresses.push_back(*(ULONG*)&buffer[8]);
					//отправка адресату: ip, команда, ширина поля, высота поля
					int lenght = sprintf(buffer, "TAKE_CONFIG%lu%hu%hu%c",server_address, map_width, map_height);
					sendto(trans_sock, buffer, lenght, 0, (sockaddr*)&players_addresses.back(), sizeof(players_addresses.back()));
				}
			}
	}
	void send_game_data_loop() {
		std::thread monitor(this, &multiplayer::key_monitor);
		while (is_play) {
			int walls_count = game->getMap().getAdditionWalls().size();
			auto lenght = sprintf(buffer, "WALLS%lu%llu", server_address, game->getMap().getAdditionWalls().size());
			memcpy(buffer + lenght, game->getMap().getAdditionWalls().data(), walls_count * sizeof(int));
			sendto(trans_sock, buffer, lenght + walls_count * sizeof(Point2d), 0, (sockaddr*)&broadcast_addr, sizeof(broadcast_addr));

			lenght = sprintf(buffer, "APPLES%lu%llu", server_address, game->getCountApples());
			int temp_counter = 0;
			for (auto apple : game->getApples())
				((Point2d*)&buffer[18])[temp_counter++]= apple.first;
			sendto(trans_sock, buffer, lenght + game->getCountApples() * sizeof(Point2d), 0, (sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
			
			for (int player = 0; player < game->getAllPlayers().size();player++) {
				lenght = sprintf(buffer, "PLAYER%lu%llu", players_addresses[player], game->getPlayer(player).getBody().size());
				int segment_num = 0;
				for (auto segment : game->getPlayer(player).getBody())
					((Point2d*)&buffer[18])[segment_num++] = segment;
				sendto(trans_sock, buffer, lenght + game->getPlayer(player).getBody().size() * sizeof(Point2d), 0, (sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
			}
		}
		is_play = false;
		monitor.join();
	}
	//запускается в отдельном потоке
	void key_monitor() {
		int wait_connect = 5;
		char buff[64];
		while (is_play && wait_connect) {
			if (auto lenght = recv(recieve_sock, buff, 1024, 0) > 0) {
				wait_connect = 5;
				if (strncmp(buff, "KEY", 3) == 0)
					for (int i = 0; i < players_addresses.size(); i++)
						if (*(ULONG*)&buff[3] == players_addresses[i])
							game->setNewDirection(i, { *(int*)&buff[7],*(int*)&buff[11] });
			}
			else
				wait_connect--;
		}
	}
};
bool is_play_now = true;


class client {
private:
	UINT16 transive_port = 33334,
		recieve_port = 33333;
	SOCKET trans_sock,
		recieve_sock;
	ULONG server_addr, 
		client_addr;
	SOCKADDR_IN broadcast_address;
	bool is_play,
		is_move;
	std::pair<sf::Keyboard::Key, Point2d> commands[4];
	char buffer[1024];//буфер для приема информации
	Painter painter;
	Map* map;
	std::list<std::pair<Point2d, AppleType>> apples;
	std::vector<Point2d> body;
public:
	client() {
		WSADATA wsaData;                        //     init of the Winsock DLL
		WSAStartup(0x0202, &wsaData);        // 
		recieve_sock = net_utils::make_socket(recieve_port);
		trans_sock = net_utils::make_socket(transive_port);
		net_utils::get_broadcast_address(trans_sock, broadcast_address, transive_port);
		client_addr = net_utils::get_local_address();

		commands[0] = std::make_pair(sf::Keyboard::S, Point2d(0, 1));
		commands[1] = std::make_pair(sf::Keyboard::A, Point2d(-1, 0));
		commands[2] = std::make_pair(sf::Keyboard::D, Point2d(1, 0));
		commands[3] = std::make_pair(sf::Keyboard::W, Point2d(0, -1));
	}
	void refresh_server_list() {
		unsigned char num_of_players;
		std::string servername;
		send(trans_sock, "WANA_PLAY", 10, 0);
		int i = 3;
		while (i) {
			if (auto length = recv(recieve_sock, buffer, 1024, 0) > 0)
				if (strncmp(buffer, "IM_SERVER", 9) == 0) {
					memcpy(&server_addr, &buffer[9], 4);
					num_of_players = buffer[13];
					servername = std::string(&buffer[16], *(unsigned short*)&buffer[14]);
				}
				else
					i--;
		}
	}

	void key_capture_loop(sf::RenderWindow& window) {
		sf::Event event;
		char buf[64];
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) window.close();
				if (is_play_now) {
					for (int commandIndex = 0; commandIndex < 4; commandIndex++) {
						if (event.key.code == commands[commandIndex].first) {
							int lenght = sprintf(buf, "KEY%lu%d%d", client_addr, commands[commandIndex].second.x, commands[commandIndex].second.y);
							sendto(trans_sock, buf, lenght, 0, (sockaddr*)&broadcast_address, sizeof(broadcast_address));
						}
					}
				}
			}
		}
		is_play = is_play_now = false;
	}

	void connect_to_server(std::string player_name, sf::RenderWindow &window) {
		unsigned short map_width, map_height;
		//Отправлять свой ip адрес(четыремя байтами) и имя
		int lenght = sprintf(buffer, "IM_PLAY%lu%c%s", client_addr, player_name.size(), player_name.c_str());
		//Информация о клиенте (ответ, ip, размер имени, имя
		sendto(trans_sock, buffer, lenght, 0, (sockaddr*)&broadcast_address, sizeof(broadcast_address));
		//ожидание получения команды о передаче информации о размере поля
		int wait = 20 / TIMEOUT;
		while (wait) {
			if (auto lenght = recv(recieve_sock, buffer, 1024, 0) >= 19) {
				//проверка 
				if (strncmp(buffer, "TAKE_CONFIG", 11) == 0&& memcpy(&buffer[11], &client_addr, 4) == 0) {
					memcpy(&map_width, &buffer[15], 2);
					memcpy(&map_height, &buffer[17], 2);
					map = new Map(map_width, map_height);
					map->initWalls();
					break;
				}
			}
			else
				wait--;
		}

		std::thread monitor(this, &client::key_capture_loop, window);

		int wait_connect = 5;
		is_play = true;
		while (is_play && wait_connect) {
			if (auto lenght = recv(recieve_sock, buffer, 1024, 0) > 0) {
				wait_connect = 5;
				if (strncmp(buffer, "WALLS", 5)==0&&memcpy(&buffer[5],&server_addr,4)==0) {
					if (map->getAdditionWalls().size() != *(size_t*)&buffer[9])
						for (int cur_wall = map->getAdditionWalls().size(); cur_wall < *(size_t*)&buffer[9]; cur_wall++)
							//проверить это говно
							map->addAdditionWall(((Point2d*)&buffer[17])[cur_wall]);
				}
				if (strncmp(buffer, "APPLES", 6) == 0 && memcpy(&buffer[6], &server_addr, 4) == 0) {
					for (size_t cur_apple = 0; cur_apple < *(size_t*)&buffer[10]; cur_apple++) {
						int tmp_cur = 0;
						for (auto apple : apples)
							if (!(apple.first == ((Point2d*)&buffer[18])[cur_apple]))
								tmp_cur++;
						if(tmp_cur!= *(size_t*)&buffer[10])
							apples.push_back({ ((Point2d*)&buffer[18])[cur_apple], AppleType::NO_BONUS });
					}
				}
				if (strncmp(buffer, "PLAYER", 6) == 0 && memcpy(&buffer[6], &client_addr, 4) == 0) {
					body.clear();
					for (size_t cur_segment = 0; cur_segment < *(size_t*)&buffer[10]; cur_segment++)
						body.push_back(((Point2d*)&buffer[18])[cur_segment]);
				}
				if (strncmp(buffer, "DEAD", 4) == 0 && memcpy(&buffer[4], &client_addr, 4) == 0)
					is_play = false;
			}
			else
				wait_connect--;

			window.clear();
			painter.drawGrid(*map, window);
			painter.drawPlayer(body.data(),body.size(), *map, window);
			painter.drawApples(apples, *map, window);
			painter.drawWalls(*map, window);
			window.display();
		}
		monitor.join();
	}
	void leave_server() {
		is_play = false;
		is_play_now = false;
	}

};