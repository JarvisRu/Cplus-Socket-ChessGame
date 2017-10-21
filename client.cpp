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

    SOCKET client_socket;
    // Address information about where it want to connect
    SOCKADDR_IN addr;
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234); // bind with TCP server port

    // connect : int connect (SOCKET s, const struct sockaddr* addr, int addrlen)
    if(connect(client_socket,(SOCKADDR*)&addr, sizeof(addr))<0){
        cout<<"連線失敗!請確認server端已開啟 ";
    }
    else{
        char message[100];
        ZeroMemory(message, 100);
        recv(client_socket,message,sizeof(message),0);
        cout<<message<<endl;

        //規則說明
        cout<<"【三子棋】"<<endl;
        cout<<"1. 棋盤如下"<<endl;
        cout<<"2. 雙方各執三子，依序放入棋盤中，三子全下完後，才可移動"<<endl;
        cout<<"3. 移動方式可直走，橫走，也可對角線走，先三子連成一線者獲勝（直線or斜線皆可）"<<endl;
        paint();
        cout<<"開始遊戲 ? (1)開始 (0)結束 :";
        int start=0;
        int over = 0;
        char *sendbuf;
        while(cin>>start){
           // start the game
            if(start==1){
                sendbuf="玩家進入";
                send(client_socket, sendbuf, (int)strlen(sendbuf), 0);
                Sleep(1000);
                system("cls");
                paint();
            }
            // end the game
            else if(start==0){
                closesocket(client_socket);
                return 0;
            }
            // if input wrong
            else{
                cout<<"請輸入 數字1(開始) 或 數字0(結束):";
            }
        }
    }
    // send : int send (SOCKET s, const char* buffer, int len, int flags)
//     char *sendbuf = "sending test!";
//     send(client_socket, sendbuf, sizeof(sendbuf), 0);

    // recv : int recv (SOCKET s, char *buf, int len, int flags)





    // closesocket(client_socket);

    return 0;
}
