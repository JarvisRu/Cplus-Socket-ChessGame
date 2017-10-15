#include <WinSock2.h>
#include <assert.h>
#include <iostream>
using namespace std;

int main(){
    WSADATA wsaData;
    WORD version = MAKEWORD(2,1); // version
    int result = WSAStartup(version, &wsaData); // success -> return 0
    if(result){
        cout<<"WinSock initialize error ! ";
    }

    // create socket descriptor : SOCKET socket (int af, int type, int protocol)
    SOCKET server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server_socket == INVALID_SOCKET){
        cout<<"Socket error ! ";
    }

    // set server address information
    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);

    // bind  : int bind (SOCKET s, const struct SOCKADDR* addr, int addrlen)
    // if success -> return 0
    int r = bind(server_socket, (SOCKADDR*)&addr, sizeof(addr));
    assert(r>=0);

    // listen : int listen (SOCKET s, int backlog);
    // if success -> return 0
    int l = listen(server_socket,SOMAXCONN);

    // accept : SOCKET accept (SOCKET s, struct sockaddr *addr, int *addrlen)

    SOCKET sConnect;
    SOCKADDR_IN client_Addr; // client address information
    int client_Addr_Len = sizeof(client_Addr);
    sConnect = accept(server_socket, (SOCKADDR*)&client_Addr, &client_Addr_Len);
    if(sConnect != INVALID_SOCKET){
        cout<<"Got connection from "<<inet_ntoa(client_Addr.sin_addr);
    }

    return 0;
}
