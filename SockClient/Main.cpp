#include "Functions.h"
#define MAX 128

int main(int argc, char* argv[]) {

	if (argc <= 2) {
		printf("Usage: SockClient.exe [IP Address] [Port]");
		exit(1);
	}
	else {

		PCHAR IPAddress = argv[1];
		PCHAR port = argv[2];

		char message[MAX] = { 0 };
		printf("Message to send: ");
		fgets(message, MAX, stdin);

		wsaCreate();
		sockCreateAndSend(IPAddress, port, message);
	}
	WSACleanup();
	return 0;
}