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
                    cout<<"��";
                    break;
                case 2:
                    cout<<"�X";
                    break;
                case 3:
                    cout<<"�@";
                    break;
                case 4:
                    cout<<"��";
                    break;
                case 5:
                    cout<<"�W";
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
        cout<<"�s�u����!�нT�{server�ݤw�}�� ";
    }
    else{
        char message[100];
        ZeroMemory(message, 100);
        recv(client_socket,message,sizeof(message),0);
        cout<<message<<endl;

        //�W�h����
        cout<<"�i�T�l�ѡj"<<endl;
        cout<<"1. �ѽL�p�U"<<endl;
        cout<<"2. ����U���T�l�A�̧ǩ�J�ѽL���A�T�l���U����A�~�i����"<<endl;
        cout<<"3. ���ʤ覡�i�����A��A�]�i�﨤�u���A���T�l�s���@�u����ӡ]���uor�׽u�ҥi�^"<<endl;
        paint();
        cout<<"�}�l�C�� ? (1)�}�l (0)���� :";
        int start=0;
        int over = 0;
        char *sendbuf;
        while(cin>>start){
           // start the game
            if(start==1){
                sendbuf="���a�i�J";
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
                cout<<"�п�J �Ʀr1(�}�l) �� �Ʀr0(����):";
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
