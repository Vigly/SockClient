#include "Functions.h"

INT main() {

	PCHAR IPAddress;
	int IPSize = 16; //15 + NULL terminator
	IPAddress = (char*)malloc(sizeof(char) * IPSize);
	printf("Please enter IPv4 address to connect to: ");
	fgets(IPAddress, IPSize, stdin);
	IPAddress[strcspn(IPAddress, "\n")] = 0;

	PCHAR port;
	int portSize = 6; //5 + NULL Terminator
	port = (char*)malloc(sizeof(char) * portSize);
	printf("Please enter port to connect to: ");
	fgets(port, portSize, stdin);
	port[strcspn(port, "\n")] = 0;

	PCHAR message;
	int messageSize = 51; //50 + NULL Terminator
	message = (char*)malloc(sizeof(char) * messageSize);
	printf("Please enter message to send: ");
	fgets(message, messageSize, stdin);
	message[strcspn(message, "\n")] = 0;

	wsaCreate();
	sockCreateAndSend(IPAddress, port, message); //Passes IP and Port
}