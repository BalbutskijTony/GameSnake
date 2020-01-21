#pragma once
#if defined(_WIN32) || defined(_WIN64)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define addr_len int                    //
#include <winsock2.h>                   // Windows
#include <windows.h>                    //  socket
#pragma comment(lib, "Ws2_32.lib")      //
#else
#define SOCKET int                      //
#define SOCKADDR_IN sockaddr_in         //
#define addr_len socklen_t              // Linux socket
#include <arpa/inet.h>                  //
#endif
#include <thread>
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
SOCKET _socket;

SOCKADDR_IN address = { 0 };
SOCKADDR_IN broadcast_address = { 0 };

#if defined(_WIN32) || defined(_WIN64)
#define prst_ch (char)254
#else
#define prst_ch '0'
#endif

addr_len client_address_length = sizeof(address);

char* file = nullptr; // Pointer to file in RAM
size_t file_length;    // File szie in bytes
char buffer[1024];
int mtu;
char addr[] = "192.168.1.0";
void init_sock() {

#if defined(_WIN32) || defined(_WIN64)		//
	WORD socketVer;                         // Initialize use
	WSADATA wsaData;                        //     of the Winsock DLL
	socketVer = MAKEWORD(2, 2);             //         by a process.
	WSAStartup(socketVer, &wsaData);        // 
#endif										//

	mtu = 100;                //
	int port = 33333;
	_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);   //
	if (_socket < 0) {                                   // Create socket with
		std::cout << "Can't create socket" << std::endl; //     datagram-based protocol
		exit(1);                                         //
	}                                                    //

	address.sin_family = AF_INET;                         //
	address.sin_port = htons(port);   // Create local address
	address.sin_addr.s_addr = INADDR_ANY;                 //

	broadcast_address.sin_family = AF_INET;                         // Create broadcast
	broadcast_address.sin_port = htons(port);   //       address

	if (1) {                   //
#if defined(_WIN32) || defined(_WIN64)										// Give access to
		char broadcastEnable = '1';                                         //  broadcast address
#else																		//
		int broadcastEnable = 1;                                            //
#endif																		//

		if (setsockopt(_socket, SOL_SOCKET, SO_BROADCAST,                   //
			&broadcastEnable, sizeof(broadcastEnable)) == 0) {				//
			std::cout << "Got access to broadcast" << std::endl;            //
		}																	//
		else {																//
			std::cerr << "Cant't get access to broadcast" << std::endl;     //
			exit(1);                                                        //
		}                                                                   // If option 'broadcast' is yes
		broadcast_address.sin_addr.s_addr = INADDR_BROADCAST;               // change server address
	}																		//
	else {																	// to broadcast
		broadcast_address.sin_addr.s_addr =                                 // Else change server address
			inet_addr(addr);												// to address in option
	}                                                                       //

	if (bind(_socket, (sockaddr*)&address, sizeof(address)) == 0)					//
		std::cout << "Bind socket" << std::endl;									//
	else {																			// Bind socket to
		std::cerr << "Can't bind socket" << std::endl;								//     client address
		exit(1);																	//
	}																				//

#if defined(_WIN32) || defined(_WIN64)											//
	int tv = 1 * 1000;  // user timeout in milliseconds [ms]                    //
	setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));		// Set socket
#else																			// receive timeout
	struct timeval tv;                                                          //        to 1 sec
	tv.tv_sec = 1;                                                              //
	tv.tv_usec = 0;                                                             //
	setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));	//
#endif	
	memcpy(buffer, "search game", 12);
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		sendto(_socket, buffer, 1024, 0, (sockaddr*)&broadcast_address, sizeof(broadcast_address));
	}

}