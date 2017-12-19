// SocketServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include <winsock.h>

#pragma comment (lib,"ws2_32.lib")

#define NO_FLAGS_SET 0

#define PORT (u_short) 44965
#define MAXBUFLEN 256

using namespace std;
INT main(VOID)
{
	WSADATA Data;
	SOCKADDR_IN serverSockAddr;
	SOCKADDR_IN clientSockAddr;
	SOCKET serverSocket;
	SOCKET clientSocket;
	int addrLen = sizeof(SOCKADDR_IN);
	int status;
	int numrcv;
	char buffer[MAXBUFLEN];

	/* initialize the Windows Socket DLL */
	status = WSAStartup(MAKEWORD(1, 1), &Data);
	/*初始化Winsock DLL
	if (status != 0)
	cerr << "ERROR: WSAStartup unsuccessful" << endl;

	/* zero the sockaddr_in structure */
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	/* specify the port portion of the address */
	serverSockAddr.sin_port = htons(PORT);
	/* specify the address family as Internet */
	serverSockAddr.sin_family = AF_INET;
	/* specify that the address does not matter */
	/*INADDR_ANY 的具体含义是，绑定到0.0.0.0。此时，对所有的地址都将是有效的
	serverSockAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	/* create a socket */
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
		cerr << "ERROR: socket unsuccessful" << endl;

	/* associate the socket with the address */
	status = bind(serverSocket, (LPSOCKADDR)&serverSockAddr,
		sizeof(serverSockAddr));
	if (status == SOCKET_ERROR)
		cerr << "ERROR: bind unsuccessful" << endl;

	/* allow the socket to take connections */
	status = listen(serverSocket, 1);
	if (status == SOCKET_ERROR)
		cerr << "ERROR: listen unsuccessful" << endl;

	/* accept the connection request when one is received */
	clientSocket = accept(serverSocket,
		(LPSOCKADDR)&clientSockAddr,
		&addrLen);

	cout << "Got the connection..." << endl;

	while (1)
	{
		numrcv = recv(clientSocket, buffer,
			MAXBUFLEN, NO_FLAGS_SET);
		if ((numrcv == 0) || (numrcv == SOCKET_ERROR))
		{
			cout << "Connection terminated." << endl;
			status = closesocket(clientSocket);
			if (status == SOCKET_ERROR)
				cerr << "ERROR: closesocket unsuccessful"
				<< endl;
			status = WSACleanup();
			if (status == SOCKET_ERROR)
				cerr << "ERROR: WSACleanup unsuccessful"
				<< endl;
			return(1);
		}
		cout << buffer << endl;
	} /* while */
}


