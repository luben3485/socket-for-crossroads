#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
typedef int SOCKET;
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

class WgSocket{
	private:
		SOCKET m_Socket;
	public:
		WgSocket(void);
		~WgSocket();
		bool IsOpened(void) const; 
		bool Open(const char* hostaddr,int port); //for client  socket() + connect()
		void Close(void);
		bool WaitInputData(int seconds); //????
		bool Read(char* receiveMessage);
		bool Write(char* message);
		bool Listen(int port);
		bool Accept(SOCKET &socket);
		void SetSocket(SOCKET socket);
};
