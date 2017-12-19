// SocketUDPServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include <winsock.h>

#pragma comment (lib,"ws2_32.lib")

#define NO_FLAGS_SET 0

#define PORT (u_short) 44965
#define MAXBUFLEN 256
#define SRC_IP_ADDR "127.0.0.1" //Client address

using namespace std;
INT main(VOID)
{
	WSADATA Data;
	SOCKADDR_IN serverSockAddr;
	SOCKADDR_IN clientSockAddr;
	SOCKET serverSocket;
	SOCKET clientSocket;
	unsigned long srcAddr;
	int addrLen = sizeof(SOCKADDR);
	int status;
	int numrcv;
	char buffer[MAXBUFLEN];

	/* initialize the Windows Socket DLL */
	status = WSAStartup(MAKEWORD(1, 1), &Data);
	/*初始化Winsock DLL*/
	if (status != 0)
		cerr << "ERROR: WSAStartup unsuccessful" << endl;
	else
		cout << "WSAStartup()..." << endl;

	/* zero the sockaddr_in structure */
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	/* specify the port portion of the address */
	serverSockAddr.sin_port = htons(PORT);
	/* specify the address family as Internet */
	serverSockAddr.sin_family = AF_INET;
	/* specify that the address does not matter */
	/*INADDR_ANY 的具体含义是，绑定到0.0.0.0。此时，对所有的地址都将是有效的*/
	serverSockAddr.sin_addr.s_addr=htonl(INADDR_ANY);

	/* create a socket */
	serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket == INVALID_SOCKET)
		cerr << "ERROR: socket unsuccessful" << endl;
	else
		cout << "socket()..." << endl;

	/* associate the socket with the address */
	status = bind(serverSocket, (SOCKADDR*)&serverSockAddr,
		sizeof(SOCKADDR));
	if (status == SOCKET_ERROR)
		cerr << "ERROR: bind unsuccessful" << endl;
	else
		cout << "bind()..." << endl;



	cout << "Wait Data..." << endl;



	/* create a socket */
	/*
	clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientSocket == INVALID_SOCKET)
		cerr << "ERROR: socket unsuccessful" << endl;
*/

	while (1)
	{
		numrcv = recvfrom(serverSocket, buffer,
			MAXBUFLEN, NO_FLAGS_SET,(SOCKADDR*)&clientSockAddr,&addrLen);

		if (!((numrcv == 0) || (numrcv == SOCKET_ERROR))) {
			cout<<" recive :  "<<buffer << endl;
			sendto(serverSocket, "From UDP Server !", sizeof("From UDP Server !"), NO_FLAGS_SET, (SOCKADDR*)&clientSockAddr, addrLen);
			memset(buffer, 0, sizeof(buffer));
		}
		/*
		if (n >= 15)
		{
			cout << "Connection terminated." << endl;
			status = closesocket(serverSocket);
			if (status == SOCKET_ERROR)
				cerr << "ERROR: closesocket unsuccessful"
				<< endl;
			status = WSACleanup();
			if (status == SOCKET_ERROR)
				cerr << "ERROR: WSACleanup unsuccessful"
				<< endl;
			return(1);
		}
		*/
	} /* while */
}


