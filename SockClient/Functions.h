#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#include <WinSock2.h>
#include <ws2tcpip.h>

WSADATA wsaData;

struct addrinfo *result = NULL, *ptr = NULL, sockHints;

int errCheck;

//Initialize winsock
void wsaCreate() {
	//Supports WSA versions 2 - 2.2
	errCheck = WSAStartup(MAKEWORD(2, 2.2), &wsaData);
	if (errCheck != 0) {
		printf("WSA startup failed: %d\n", WSAGetLastError());
		WSACleanup();
	}
	else {
		printf("WSA startup was successful\n");
	}
}

void sockCreateAndSend(PCHAR IPAddress, PCHAR port, PCHAR message) {
	ZeroMemory(&sockHints, sizeof(sockHints));
	sockHints.ai_family = AF_INET; //IPv4
	sockHints.ai_socktype = SOCK_STREAM; //two-way connection-based byte streams
	sockHints.ai_protocol = IPPROTO_TCP; //TCP

	//Resolves server address and port
	errCheck = getaddrinfo(IPAddress, port, &sockHints, &result);
	if (errCheck != 0) {
		printf("getaddrinfo failed: %d\n", WSAGetLastError());
		WSACleanup();
	}
	else {
		printf("Resolution of getaddrinfo successful\n");
	}

	//Initialize SOCKET object
	SOCKET ConnectSocket = INVALID_SOCKET;
	
	//Connect to address called by getaddrinfo
	ptr = result;

	//Create SOCKET object for connecting to server and specify socket parameters
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
	}
	else {
		printf("Socket creation successful");
	}

	//Socket connects to server
	errCheck = connect(ConnectSocket, ptr->ai_addr, ptr->ai_addrlen);
	if (errCheck == SOCKET_ERROR) {
		printf("Error connecting socket %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
	}

	errCheck = send(ConnectSocket, message, (int)strlen(message), 0);
	if (errCheck == SOCKET_ERROR) {
		printf("Failed to send buffer data: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
	}
	else {
		printf("Data successfully sent\n");
	}

	printf("Bytes sent: %ld\n", errCheck);

	errCheck = shutdown(ConnectSocket, SD_SEND);
	if (errCheck == SOCKET_ERROR) {
		printf("Error shutting down socket: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
	}
	else {
		printf("Socket shutdown successful\n");
	}

	//Socket cleanup
	closesocket(ConnectSocket);
	WSACleanup();
}