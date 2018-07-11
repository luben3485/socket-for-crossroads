#include <iostream>
#include "socket_cross_roads.hpp"

void process_client(SOCKET socket){
	WgSocket client_socket;
	client_socket.SetSocket(socket);
	char receiveMessage[256] = {};
	char message[] = {"fuckyoutoo"};

	client_socket.Read(receiveMessage);
	printf("Client%d:%s\n",socket,receiveMessage);
	client_socket.Write(message);
}

int main(){
	
	WgSocket server_socket;
	bool s = server_socket.Listen(1487);
	if(!s) return false;
	while(1){
		SOCKET socket;
		if(!server_socket.Accept(socket)) continue;
		process_client(socket);
	}

	return 0;
}
