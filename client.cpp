#pragma comment(lib, "Ws2_32.lib")
#include<WinSock2.h>
#include<windows.h>
#include <cstdlib>
#include<assert.h>
#include<iostream>
#include<string>

using namespace std;

// declare function
void paint(int, int, int);        // paint board
bool check(int, int, int, int);   // check if the input is correct and no conflict
bool win();                       // judge if someone win
void reBoard();                   // reassign value of board

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
int s_x, s_y, e_x, e_y;

int main(){
    WSADATA wsaData;
    WORD version = MAKEWORD(2,1); // version
    int result = WSAStartup(version, &wsaData); // success -> return 0
    if(result) {
        cout << "WinSock initialize error ! ";
    }

    SOCKET client_socket;
    // Address information about where it want to connect
    SOCKADDR_IN addr;
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    while(true) {
        cout << "Please choose (1)Setting Server IP (2)Own(127.0.0.1) :";
        int IPset=0;
        cin >> IPset;
        if(IPset == 1) {
            string IP;
            cout << "IP:";
            cin >> IP;
            addr.sin_addr.s_addr = inet_addr(IP.c_str());
            cout << "Setting " << IP << " as Server IP, waiting for connection" << endl;
            break;
        }
        else if(IPset == 2) {
            addr.sin_addr.s_addr = inet_addr("127.0.0.1");
            cout <<"Connect to own, waiting for connection" << endl;
            break;
        }
        else{
            cout << "Error input ! Plz input 1 or 2" << endl;
        }
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(123); // bind with TCP server port

    // connect : int connect (SOCKET s, const struct sockaddr* addr, int addrlen)
    if(connect(client_socket,(SOCKADDR*)&addr, sizeof(addr))<0) {
        cout << "�s�u����!�нT�{server�ݤw�}�� ";
    }
    else{
        char message[100];
        ZeroMemory(message, 100);
        recv(client_socket, message, sizeof(message), 0);
        cout << message << endl;

        Sleep(1000);
        system("cls");

        // for rule
        cout << "�i�T�l�ѡj" << endl;
        cout << "=================================================================================" << endl;
        cout << "1. �ѽL�p�U" << endl;
        cout << "2. ����U���T�l�A�̧ǩ�J�ѽL���A�T�l���U����A�~�i����" << endl;
        cout << "3. ���ʤ覡�i�����B��A�]�i�﨤�u���]�p�ϡ^�A���T�l�s���@�u����ӡ]���u�B�׽u�ҥi�^" << endl;
        cout << "4. �U�Ѥ覡�G��J�@1~9(�N���I) + 0 + 0" << endl;
        cout << "  EX: 100 �� �U�b�I1" << endl;
        cout << "  1 2 3\n  4 5 6\n  7 8 9\n";
        cout << "5. ���ʤ覡�G��J �_�l�I + 0 + ���ʨ쪺�I" << endl;
        cout << "  EX: 105 �� �I1���ʨ��I5" << endl;
        cout << "6. �Y��J�榡���~�A�ݭ��s��J���쥿�T" << endl;
        cout << "7. Player�N��:��  Server�N��:��" << endl;
        cout << "=================================================================================" << endl;
        paint(0,0,0);
        cout << "�}�l�C�� ? (1)�}�l (0)���� :";

        char *sendbuf = new char[100];
        int start = 0;
        bool over;

        while(cin >> start) {
           // start the game
            if(start == 1) {
                sendbuf = "Player in !!";
                send(client_socket, sendbuf, (int)strlen(sendbuf), 0);

                // initialize game setting
                Sleep(1000);
                system("cls");
                paint(0,0,0);

                int run = 1;
                int chess_s = 0, chess_c = 0;
                char mov[3];
                over = false;
                // start to play
                while( !over ) {
                    // your run
                    if(run%2 == 1) {
                        if(run >= 7) cout << "(You can move now)" << endl;
                        while( true ) {
                            cout << "�A����(��)�G";
                            cin >> mov[0] >> mov[1] >> mov[2];

                            if(mov[1] != '0')
                                cout << "��J���~!! �Э��s��J" << endl;
                            else if(mov[0] == '0')
                                cout << "��J���~!! �Э��s��J" << endl;
                            else if(check(2, (int)mov[0]-48, (int)mov[2]-48, chess_c)) {
                                system("cls");
                                paint(2, (int)mov[0]-48, (int)mov[2]-48);
                                send(client_socket, mov, strlen(mov), 0);
                                break;
                            }
                            else
                                cout << "��J���~!! �Э��s��J" << endl;
                        }

                        chess_c = (chess_c < 3)? chess_c+1 : 3;
                        ++run;

                        // judge if win
                        if(win() == true){
                            cout << endl << "You win !! Server lose ~" << endl;
                            Sleep(3000);
                            over = true;
                            reBoard();
                        }
                    }
                    // player run
                    else{
                        cout << "��觽(��)" << endl;
                        // get  message
                        char mov2[10];
                        ZeroMemory(mov2, 10);
                        recv(client_socket,mov2, sizeof(mov2), 0);
                        if(check(1, (int)mov2[0]-48, (int)mov2[2]-48, chess_s)) {
                            system("cls");
                            paint(1, (int)mov2[0]-48, (int)mov2[2]-48);
                        }
                        // if Server leave
                        else{
                            cout << "Server Leave !! Exit program in 3 sec";
                            Sleep(3000);
                            closesocket(client_socket);
                            return 0;
                        }

                        chess_s = (chess_s < 3)? chess_s+1 : 3;
                        ++run;

                        // judge if win
                        if(win() == true) {
                            cout << endl << "Server win !! You lose ~ " << endl;
                            Sleep(3000);
                            over = true;
                            reBoard();
                        }
                    }
                }
            }
            // end the game
            else if(start == 0) {
                cout << endl << "Leaving the game ! Program will be closed !!";
                sendbuf = "Player leave !!";
                send(client_socket, sendbuf, (int)strlen(sendbuf), 0);

                Sleep(2000);
                closesocket(client_socket);
                return 0;
            }
            // if input wrong
            else{
                cout << "�п�J �Ʀr1(�}�l) �� �Ʀr0(����):";
            }

            if(over == true) {
                cout << "�~��C�� ? (1)�}�l (0)���� :";
            }
        }
    }
    return 0;
}

bool check(int mode, int mov, int to, int chessNum){
    // get the coord of point
    switch(mov) {
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
    if(to != 0) {
        switch(to) {
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
    if(chessNum < 3) {
        // can't move
        if(to != 0) {
            return false;
        }
        // can't set on chess which is set
        if(board[s_y][s_x]!=1) {
            return false;
        }
    }
    // can move
    else {
        // have to move
        if(to == 0) {
            return false;
        }
        // can't move others chess
        if((mode==1 && board[s_y][s_x]==6) || (mode==2 && board[s_y][s_x]==7)) {
            return false;
        }
        // can't move to somewhere which is set
        if(board[e_y][e_x]!=1) {
            return false;
        }
        // just can move to neighbor
        if(abs(e_y-s_y)>7 || abs(e_x-s_x)>8) {
            return false;
        }
        // ban : 2<->4,2<->6,4<->8,6<->8
        if((mov==2 && to==4)||(mov==4 && to==2)||(mov==2 && to==6)||(mov==6 && to==2)||(mov==4 && to==8)||(mov==8 && to==4)||(mov==6 && to==8)||(mov==8 && to==6)) {
            return false;
        }
    }
    return true;
}


// do paint
void paint(int mode,int mov, int to) {
    // server
    if(mode == 1) {
        // has move
        if(to != 0) {
            board[s_y][s_x] = 1;
            board[e_y][e_x] = 7;
        }
        // no move
        else {
            board[s_y][s_x] = 7;
        }
    }
    // client
    else if(mode == 2) {
        // has move
        if(to != 0) {
            board[s_y][s_x] = 1;
            board[e_y][e_x] = 6;
        }
        // no move
        else {
            board[s_y][s_x] = 6;
        }
    }
    // paint
    for(int row=0; row<15 ; row++) {
        for(int col=0; col<29 ; col++) {
            switch(board[row][col]) {
                case 0:
                    cout << " ";
                    break;
                case 1:
                    cout << "◇";
                    break;
                case 2:
                    cout << "—";
                    break;
                case 3:
                    cout << "＼";
                    break;
                case 4:
                    cout << "／";
                    break;
                case 5:
                    cout << "︱";
                    break;
                // client
                case 6:
                    cout << "▲";
                    break;
                // server
                case 7:
                    cout << "★";
                    break;

            }
        }
        cout << endl;
    }
}

bool win() {
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

void reBoard() {
    for(int i=0 ; i<=16 ; i+=8) {
        board[0][i] = 1;
        board[7][i] = 1;
        board[14][i] = 1;
    }
}
