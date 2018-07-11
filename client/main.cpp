#include <iostream>
#include "socket_cross_roads.hpp"


int main(){
	
	WgSocket socket;
	if(!socket.Open("127.0.0.1",1487)) return 1;
	char message[] = {"fuck you~~"};
	if(!socket.Write(message)) return 1;
	
	char receiveMessage[256] = {};
	socket.Read(receiveMessage);
	printf("Server:%s\n",receiveMessage);
	return 0;
}
