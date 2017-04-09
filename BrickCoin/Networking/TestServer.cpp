#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "..\TestServer.h"
#include "..\BrickDataBase\db.h"
#include "..\EBVerify.h"
#include "..\BrickCoin.h"




// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int TestServer::fireOffACoinToDatabase(std::string coinText)
{
	char * sql;
	int rc;

	DB databaseHelper;

	databaseHelper.startDatabase();

	//Must figure out how to recreate the coinSignature?
	//This parses the input string into two parts, first the PTriples and Hash data, then second into the SHA512Hash.
	char * parseChar1 = new char[coinText.length() + 1];
	strcpy(parseChar1, coinText.c_str());
	char * pch1;
	pch1 = strtok(parseChar1, "\n");
	std::string parseString = pch1;
	pch1 = strtok(NULL, "\n");
	parseString = parseString + "\n" + pch1;
	pch1 = strtok(NULL, "\n");
	std::string SHA512hash = pch1;

	//ONLY for TESTING PURPOSES
	std::cout << parseString << std::endl;
	std::cout << SHA512hash << std::endl;
	EBVerify* brickFromText = new EBVerify(parseString + "\n" + SHA512hash +"\n");
	if (brickFromText->getCoin().getSignature().size()>0) {
		std::cout << "Fuck" << std::endl;
	}
	std::string coinSig = parseString + "\n" + SHA512hash + "\n";
	databaseHelper.parseAndStore(coinSig);

	/* Create SQL statement */
	sql = "SELECT * from BRICK";
	databaseHelper.getInfoFromDatabase(sql);

	std::vector<std::string> data;
	data.reserve(10);
	std::cout << "\nOutputting some stuff" << std::endl;
	std::cout << databaseHelper.getAndRecreateSignature(data, 2);
	std::cout << std::endl;
	databaseHelper.closeDatabase();
	return 0;
}

int TestServer::startServer()
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);
			fireOffACoinToDatabase(recvbuf);
			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}