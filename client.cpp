#pragma comment(lib, "Ws2_32.lib")
#include<WinSock2.h>

#include<assert.h>
#include<iostream>
using namespace std;

int main(){
    WSADATA wsaData;
    WORD version = MAKEWORD(2,1); // version
    int result = WSAStartup(version, &wsaData); // success -> return 0
    if(result){
        cout<<"WinSock initialize error ! ";
    }

    SOCKET client_socket;
    // Address information about where it want to connect
    SOCKADDR_IN addr;
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234); // bind with TCP server port

    // connect : int connect (SOCKET s, const struct sockaddr* addr, int addrlen)
    if(connect(client_socket,(SOCKADDR*)&addr, sizeof(addr))<0){
        cout<<"client connection error ! ";
    }
    // send : int send (SOCKET s, const char* buffer, int len, int flags)
    // char *sendbuf = "sending test!";
    // send(client_socket, sendbuf, sizeof(sendbuf), 0);

    // recv : int recv (SOCKET s, char *buf, int len, int flags)
    char message[100];
    ZeroMemory(message, 100);
    recv(client_socket,message,sizeof(message),0);
    cout<<message<<endl;

    closesocket(client_socket);

    return 0;
}
