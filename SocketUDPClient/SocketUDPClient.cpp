// SocketUDPClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <windows.h>
#include <iostream>
#include <winsock.h>
#pragma comment (lib,"ws2_32.lib")

using namespace std;

#define NO_FLAGS_SET 0

#define PORT (u_short) 44965
#define MAXBUFLEN 256
#define DEST_IP_ADDR "127.0.0.1" //Server address

INT main(VOID)
{
	WSADATA Data;
	SOCKADDR_IN destSockAddr;
	SOCKET destSocket;
	unsigned long destAddr;
	int status;
	int numsnt;
	char *toSendtxt = "Test String";
	int numrcv;
	char buffer[MAXBUFLEN];
	int addrLen = sizeof(destSockAddr);
	/* initialize the Windows Socket DLL */
	status = WSAStartup(MAKEWORD(1, 1), &Data);
	if (status != 0)
		cerr << "ERROR: WSAStartup unsuccessful"<< endl;
	else
	{
		cout << "WSAStartup()... " << endl;
	}
	/* convert IP address into in_addr form */
	destAddr = inet_addr(DEST_IP_ADDR);
	/* copy destAddr into sockaddr_in structure */
	memcpy(&destSockAddr.sin_addr,
		&destAddr, sizeof(destAddr));
	/* specify the port portion of the address */
	destSockAddr.sin_port = htons(PORT);
	/* specify the address family as Internet */
	destSockAddr.sin_family = AF_INET;

	/* create a socket */
	destSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (destSocket == INVALID_SOCKET)
	{
		cerr << "ERROR: socket unsuccessful" << endl;
		status = WSACleanup();
		if (status == SOCKET_ERROR)
			cerr << "ERROR: WSACleanup unsuccessful"
			<< endl;
		return(1);
	}
	else
	{
		cout << "socket()... " << endl;
	}

	/* associate the socket with the address */
	/*
	status = bind(destSocket, (SOCKADDR*)&destSockAddr,
		sizeof(destSockAddr));
	if (status == SOCKET_ERROR) {
		cerr << "ERROR: bind unsuccessful" << endl;
		cout << "即将退出..." << endl;
		Sleep(3000);
		return(1);
	}	
	else
	{
		cout << "bind()... " << endl;
	}
	*/
	cout << "Send to IP Address: "
		<< DEST_IP_ADDR << endl;

	int n = 0;
	while (1)
	{
		cout << "Sending..." << endl;
		numsnt = sendto(destSocket, toSendtxt,
			strlen(toSendtxt) + 1, NO_FLAGS_SET, (SOCKADDR*)&destSockAddr, addrLen);
	
		numrcv = recvfrom(destSocket, buffer,
			MAXBUFLEN, NO_FLAGS_SET, (SOCKADDR*)&destSockAddr, &addrLen);

		if (n > 20) {

			cout << "Send faild, the size is over 20" << endl;
			status = closesocket(destSocket);
			if (status == SOCKET_ERROR)
				cerr << "ERROR: closesocket unsuccessful"
				<< endl;
			status = WSACleanup();
			if (status == SOCKET_ERROR)
				cerr << "ERROR: WSACleanup unsuccessful"
				<< endl;
			cout << "即将退出..." << endl;
			Sleep(3000);
			return(1);
		}

		if((numrcv == 0) || (numrcv == SOCKET_ERROR) || n >= 20)
		{
			continue;
		}
		else {
			cout << "recive : " << buffer <<" " <<n++ << endl;
			memset(buffer, 0, sizeof(buffer));
		}
		
		/* Wait before sending the message again */
		Sleep(4800);
	} /* while */
}



