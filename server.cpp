#pragma comment(lib, "Ws2_32.lib")
#include<WinSock2.h>
#include<windows.h>
#include <cstdlib>
#include<assert.h>
#include<iostream>
#include<string>
using namespace std;

int board[15][29]= {
        {1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0},
        {5,0,3,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,4,0,5},
        {5,0,0,0,3,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,4,0,0,0,5},
        {5,0,0,0,0,0,3,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,4,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,0,3,0,0,0,0,0,5,0,0,0,0,0,4,0,0,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,0,0,0,3,0,0,0,5,0,0,0,4,0,0,0,0,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,3,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,5},
        {1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0},
        {5,0,0,0,0,0,0,0,0,0,0,0,4,0,5,0,3,0,0,0,0,0,0,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,0,0,0,4,0,0,0,5,0,0,0,3,0,0,0,0,0,0,0,0,0,5},
        {5,0,0,0,0,0,0,0,4,0,0,0,0,0,5,0,0,0,0,0,3,0,0,0,0,0,0,0,5},
        {5,0,0,0,0,0,4,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,3,0,0,0,0,0,5},
        {5,0,0,0,4,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,3,0,0,0,5},
        {5,0,4,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,3,0,5},
        {1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0}};

void paint(){
    for(int row=0; row<15 ; row++){
        for(int col=0; col<29 ; col++){
            switch(board[row][col]){
                case 0:
                    cout<<" ";
                    break;
                case 1:
                    cout<<"◇";
                    break;
                case 2:
                    cout<<"—";
                    break;
                case 3:
                    cout<<"＼";
                    break;
                case 4:
                    cout<<"／";
                    break;
                case 5:
                    cout<<"︱";
                    break;
            }
        }
        cout<<endl;
    }
}

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
    assert(l>=0);
    cout<<"等待玩家連線.."<<endl;

    // accept : SOCKET accept (SOCKET s, struct sockaddr *addr, int *addrlen)
    SOCKET sConnect;
    SOCKADDR_IN client_Addr; // client address information
    int client_Addr_Len = sizeof(client_Addr);
    sConnect = accept(server_socket, (SOCKADDR*)&client_Addr, &client_Addr_Len);

    // if connect -> send message to client
    if(sConnect != INVALID_SOCKET){
        cout<<"Got connection from "<<inet_ntoa(client_Addr.sin_addr)<<endl;
        cout<<"等待玩家進入遊戲..";

        char *sendbuf;
        sendbuf = "Connect successfully to server！";
        send(sConnect, sendbuf, (int)strlen(sendbuf), 0);

        char message[100];
        ZeroMemory(message, 100);
        recv(sConnect,message,sizeof(message),0);
        cout<<message;

        Sleep(1000);
        system("cls");
        paint();

    }

    return 0;
}
