#include "socket_cross_roads.hpp"

WgSocket::WgSocket(void){
	m_Socket = INVALID_SOCKET;
}

WgSocket::~WgSocket(){
	Close();
}
bool WgSocket::IsOpened(void) const{
	if(m_Socket == INVALID_SOCKET) return false;
	else return true;
}
bool WgSocket::Open(const char* hostaddr, int port){
	Close();
	struct sockaddr_in info;
	bzero(&info,sizeof(info));
	info.sin_family = PF_INET;
	info.sin_addr.s_addr = inet_addr(hostaddr);
	info.sin_port = htons(port);
	// create socket
	try{
		m_Socket = socket(AF_INET , SOCK_STREAM,0);
	}catch(...){
		m_Socket = INVALID_SOCKET;
		return false;
	}
	// checking socket were established
	if(m_Socket == INVALID_SOCKET) return false;
	// connect to Server
	try{ //error occurs when err = -1
		int err = connect(m_Socket,(struct sockaddr *)&info,sizeof(info));
		if(err >= 0) return true;
	}catch(...){
		Close();
		return false;			
	}
}

void WgSocket::Close(void){
	if(!IsOpened())return;
	try{
		close(m_Socket);
	}catch(...){}
	m_Socket = INVALID_SOCKET;
}
bool WgSocket::Read(char* receiveMessage){
	if(!IsOpened()) return false;
	try{
		recv(m_Socket,receiveMessage,sizeof(receiveMessage),0);
		return true;
	}catch(...){
		return false;	
	}
}
bool WgSocket::Write(char* message){
	if(!IsOpened()) return false;
	try{
		send(m_Socket,message,sizeof(message),0);
		return true;
	}catch(...){
		return false;
	}
}
bool WgSocket::Listen(int port){	
	Close();
	struct sockaddr_in serverInfo;
	bzero(&serverInfo,sizeof(serverInfo));
	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;
	serverInfo.sin_port = htons(port);
	// create socket
	try{
		m_Socket = socket(AF_INET , SOCK_STREAM,0);
	}catch(...){
		m_Socket = INVALID_SOCKET;
		return false;
	}
	// checking socket were established
	if(m_Socket == INVALID_SOCKET) return false;
	
	int rc;
	//bind
	try{
		rc = bind(m_Socket,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
	}catch(...){
		rc = SOCKET_ERROR;
	}
	if(rc == SOCKET_ERROR){
		Close();
		return false;
	}
	//listen
	try{
		rc = listen(m_Socket,5);
	}catch(...){
		rc = SOCKET_ERROR;
	}
	if(rc == SOCKET_ERROR){
		Close();
		return false;
	}
	return true;
}

bool WgSocket::Accept(SOCKET &socket){
	if(!IsOpened()) return false;
	struct sockaddr_in clientInfo;
	socklen_t addrlen = sizeof(clientInfo);
	try{
		socket = accept(m_Socket, (struct sockaddr *)&clientInfo,&addrlen);
	}catch(...){
		socket = INVALID_SOCKET;
		return false;
	}
	return true;
}
void WgSocket::SetSocket(SOCKET socket){
	Close();
	m_Socket = socket;
}



 


















