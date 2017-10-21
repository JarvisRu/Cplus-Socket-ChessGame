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

// do paint
void paint(int mode,int mov, int to){
    // server
    if(mode==1){

    }
    // client
    else if(mode==2){
        // has mov
        if(to!=0){

        }
        //no mov
        else{
            if(mov==1){
                if(board[0][0]!=7){
                    board[0][0] = 6;
                }
            }
            else if(mov==2){
                if(board[0][8]!=7){
                    board[0][8] = 6;
                }
            }
            else if(mov==3){
                if(board[0][16]!=7){
                    board[0][16] = 6;
                }
            }
            else if(mov==4){

            }
            else if(mov==2){

            }
            else if(mov==3){

            }
            else if(mov==7){

            }
            else if(mov==8){

            }
            else if(mov==9){

            }
        }
    }
    // paint
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
                // client
                case 6:
                    cout<<"▲";
                    break;
                // server
                case 7:
                    cout<<"★";
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
        cout<<"================================================================================="<<endl;
        cout<<"1. 棋盤如下"<<endl;
        cout<<"2. 雙方各執三子，依序放入棋盤中，三子全下完後，才可移動"<<endl;
        cout<<"3. 移動方式可直走，橫走，也可對角線走，先三子連成一線者獲勝（直線or斜線皆可）"<<endl;
        cout<<"4. 下棋方式：輸入　1~9(代表點) + 0 + 0"<<endl;
        cout<<"  EX: 1 0 0 → 下在點1 (若輸入已存在於棋盤的自己棋→視為浪費一局)"<<endl;
        cout<<"  1 2 3\n  4 5 6\n  7 8 9\n";
        cout<<"5. 移動方式：輸入 起始點 + 0 + 移動到的點"<<endl;
        cout<<"  EX: 1 0 5 → 點1移動到點5"<<endl;
        cout<<"6. Player代表:▲  Server代表:★"<<endl;
        cout<<"================================================================================="<<endl;
        paint(0,0,0);
        cout<<"開始遊戲 ? (1)開始 (0)結束 :";

        int start = 0;
        int over = 0;
        int run = 0;
        int chess = 0;
        char *sendbuf;
        char mov[3];

        while(cin>>start){
           // start the game
            if(start==1){
                sendbuf="玩家進入";
                send(client_socket, sendbuf, (int)strlen(sendbuf), 0);

                Sleep(1000);
                system("cls");

                paint(0,0,0);
                ++run;
                while(!over){
                    // player run
                    if(run%2==1){
                        cout<<"動作：";
                        cin>>mov[0]>>mov[1]>>mov[2];
                        // has mov
                        if((int)mov[2]-48!=0){

                        }
                        // no mov
                        else{
                            system("cls");
                            paint(2,(int)mov[0]-48,0);
                        }
                        send(client_socket,mov,3, 0);
                        ++chess;
                        ++run;
                    }
                    // client run
                    else{

                    }

                }

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
