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
                // client
                case 6:
                    cout<<"��";
                    break;
                // server
                case 7:
                    cout<<"��";
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
        cout<<"================================================================================="<<endl;
        cout<<"1. �ѽL�p�U"<<endl;
        cout<<"2. ����U���T�l�A�̧ǩ�J�ѽL���A�T�l���U����A�~�i����"<<endl;
        cout<<"3. ���ʤ覡�i�����A��A�]�i�﨤�u���A���T�l�s���@�u����ӡ]���uor�׽u�ҥi�^"<<endl;
        cout<<"4. �U�Ѥ覡�G��J�@1~9(�N���I) + 0 + 0"<<endl;
        cout<<"  EX: 1 0 0 �� �U�b�I1 (�Y��J�w�s�b��ѽL���ۤv�ѡ��������O�@��)"<<endl;
        cout<<"  1 2 3\n  4 5 6\n  7 8 9\n";
        cout<<"5. ���ʤ覡�G��J �_�l�I + 0 + ���ʨ쪺�I"<<endl;
        cout<<"  EX: 1 0 5 �� �I1���ʨ��I5"<<endl;
        cout<<"6. Player�N��:��  Server�N��:��"<<endl;
        cout<<"================================================================================="<<endl;
        paint(0,0,0);
        cout<<"�}�l�C�� ? (1)�}�l (0)���� :";

        int start = 0;
        int over = 0;
        int run = 0;
        int chess = 0;
        char *sendbuf;
        char mov[3];

        while(cin>>start){
           // start the game
            if(start==1){
                sendbuf="���a�i�J";
                send(client_socket, sendbuf, (int)strlen(sendbuf), 0);

                Sleep(1000);
                system("cls");

                paint(0,0,0);
                ++run;
                while(!over){
                    // player run
                    if(run%2==1){
                        cout<<"�ʧ@�G";
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
