#pragma comment(lib, "Ws2_32.lib")
#include<WinSock2.h>
#include<windows.h>
#include <cstdlib>
#include<assert.h>
#include<iostream>
#include<string>
using namespace std;

// declare function
void paint(int,int,int);        // paint board
bool check(int,int,int,int);    // check if the input is correct and no conflict
bool win();                     // judge if someone win
void reBoard();                 // reassign value of board

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

// assign value : start point & end point
int s_x,s_y,e_x,e_y;

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
    // addr.sin_addr.s_addr = inet_addr("6.5.42.6");
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(123);

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

        while(true){
            char message[100];
            ZeroMemory(message, 100);
            recv(sConnect,message,sizeof(message),0);
            cout<<message;
            // player in
            if(message[7]=='i'){
                // initialize game setting
                Sleep(1000);
                system("cls");
                paint(0,0,0);

                bool over = false;
                int run = 1;
                int chess_s = 0, chess_c = 0;
                char mov[3];
                // start to play
                while(!over){
                    // your run
                    if(run%2==0){

                        cout<<"你的局(★)：";
                        cin>>mov[0]>>mov[1]>>mov[2];

                        system("cls");

                        // has mov
                        if((int)mov[2]-48!=0 && chess_s==3){
                            paint(1,(int)mov[0]-48,(int)mov[2]-48);
                        }
                        // no mov
                        else if(chess_s!=3){
                            paint(1,(int)mov[0]-48,0);
                        }
                        send(sConnect,mov,strlen(mov), 0);

                        chess_s = (chess_s < 3)? chess_s+1 : 3;
                        ++run;

                        // judge if win
                        if(win()==true){
                            cout<<endl<<"You win !! Player lose ~"<<endl;
                            Sleep(3000);
                            over = true;
                        }
                    }
                    // player run
                    else{
                        cout<<"對方局(▲)"<<endl;
                        // get  message
                        char mov2[10];
                        ZeroMemory(mov2, 10);
                        recv(sConnect,mov2,sizeof(mov2),0);

                        system("cls");

                        // has mov
                        if((int)mov2[2]-48!=0 && chess_c==3){
                            paint(2,(int)mov2[0]-48,(int)mov2[2]-48);
                        }
                        // no mov
                        else if(chess_c!=3){
                            paint(2,(int)mov2[0]-48,0);
                        }

                        chess_c = (chess_c < 3)? chess_c+1 : 3;
                        ++run;

                        // judge if win
                        if(win()==true){
                            cout<<endl<<"Player win !! You lose ~"<<endl;
                            Sleep(3000);
                            over = true;
                        }
                    }
                }
            }
            // player out
            else{
                cout<<endl<<"Player leave !!";
                Sleep(2000);
                break;
            }
            cout<<"等待玩家進入遊戲.."<<endl;
            reBoard();
        }
        closesocket(sConnect);

    }
    return 0;
}

void check(int mode, int mov, int to, int chessNum){
    // get the coord of point
    switch(mov){
        case 1:
            s_x = 0;
            s_y = 0;
            break;
        case 2:
            s_x = 8;
            s_y = 0;
            break;
        case 3:
            s_x = 16;
            s_y = 0;
            break;
        case 4:
            s_x = 0;
            s_y = 7;
            break;
        case 5:
            s_x = 8;
            s_y = 7;
            break;
        case 6:
            s_x = 16;
            s_y = 7;
            break;
        case 7:
            s_x = 0;
            s_y = 14;
            break;
        case 8:
            s_x = 8;
            s_y = 14;
            break;
        case 9:
            s_x = 16;
            s_y = 14;
            break;
    }
    if(to!=0){
        switch(to){
            case 1:
                e_x = 0;
                e_y = 0;
                break;
            case 2:
                e_x = 8;
                e_y = 0;
                break;
            case 3:
                e_x = 16;
                e_y = 0;
                break;
            case 4:
                e_x = 0;
                e_y = 7;
                break;
            case 5:
                e_x = 8;
                e_y = 7;
                break;
            case 6:
                e_x = 16;
                e_y = 7;
                break;
            case 7:
                e_x = 0;
                e_y = 14;
                break;
            case 8:
                e_x = 8;
                e_y = 14;
                break;
            case 9:
                e_x = 16;
                e_y = 14;
                break;
        }
    }
    // before can move
    if(chessNum < 3){
        // can't move
        if(to!=0){
            return false;
        }
        // can't set on chess which is set
        if(board[s_y][s_x]!=1){
            return false;
        }
    }
    // can move
    else{
        // have to move
        if(to==0){
            return false;
        }
        // can't move others chess
        if((mode==1 && board[s_y][s_x]==6) || (mode==2 && board[s_y][s_x]==7)){
            return false;
        }
        // can't move to somewhere which is set
        if(board[e_y][e_x]!=1){
            return false;
        }
        // just can move to neighbor
        if(abs(e_y-s_y)>7 || abs(e_x-s_x)>8){
            return false;
        }
    }
    return true;
}


// do paint
void paint(int mode,int mov, int to){
    // server
    if(mode==1){
        // has mov
        if(to!=0){
            board[s_y][s_x] = 1;
            board[e_y][e_x] = 7;
        }
        // no mov
        else{
            board[s_y][s_x] = 7;
        }
    }
    // client
    else if(mode==2){
        // has mov
        if(to!=0){
            board[s_y][s_x] = 1;
            board[e_y][e_x] = 6;
        }
        // no mov
        else{
            board[s_y][s_x] = 6;
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

bool win(){
    // scan row
    if(board[0][0]==6 && board[0][8]==6 && board[0][16]==6)         return true;
    else if(board[7][0]==6 && board[7][8]==6 && board[7][16]==6)    return true;
    else if(board[14][0]==6 && board[14][8]==6 && board[14][16]==6) return true;
    else if(board[0][0]==7 && board[0][8]==7 && board[0][16]==7)    return true;
    else if(board[7][0]==7 && board[7][8]==7 && board[7][16]==7)    return true;
    else if(board[14][0]==7 && board[14][8]==7 && board[14][16]==7) return true;
    // scan col
    else if(board[0][0]==6 && board[7][0]==6 && board[14][0]==6)    return true;
    else if(board[0][8]==6 && board[7][8]==6 && board[14][8]==6)    return true;
    else if(board[0][16]==6 && board[7][16]==6 && board[14][16]==6) return true;
    else if(board[0][0]==7 && board[7][0]==7 && board[14][0]==7)    return true;
    else if(board[0][8]==7 && board[7][8]==7 && board[14][8]==7)    return true;
    else if(board[0][16]==7 && board[7][16]==7 && board[14][16]==7) return true;
    // scan  slash
    else if(board[0][0]==6 && board[7][8]==6 && board[14][16]==6)   return true;
    else if(board[0][16]==6 && board[7][8]==6 && board[14][0]==6)   return true;
    else if(board[0][0]==7 && board[7][8]==7 && board[14][16]==7)   return true;
    else if(board[0][16]==7 && board[7][8]==7 && board[14][0]==7)   return true;
    else return false;
}

void reBoard(){
    for(int i=0 ; i<=16 ; i+=8){
        board[0][i] = 1;
        board[7][i] = 1;
        board[14][i] = 1;
    }
}
