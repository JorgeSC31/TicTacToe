#include <iostream>
#include <windows.h>

using namespace std;

char board[9];
string moves[9];
int moveN=0;

void colorBlue();
void colorGreen();
void colorCyan();
void colorRed();
void colorPink();
void colorYellow();
void colorWhite();
void colorError();
void colorPick(char board);

void menu();
void drawGame();
void game(int option);
int computerPlay(char turn, int depth);
int Win();
int Tie();



int main()
{
    menu();
    return 0;
}



void colorBlue()
{
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
}
void colorGreen()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
}
void colorCyan()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
}
void colorRed()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
}
void colorPink()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
}
void colorYellow()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
}
void colorWhite()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
void colorError()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),75);
}
void colorPick(char board)
{
    switch (board) {
        case 'X': colorCyan(); break;
        case 'O': colorRed(); break;
        default: colorGreen(); break;
    }
    cout << board;
}



void menu()
{
    for(int i=0; i<9; i++)board[i]=i+'1';
    for(int i=0; i<9; i++)moves[i]="";
    moveN=0;
    int option = -1;
    do {
        system("cls");
        colorCyan();
        cout << "                Tic Tac Toe" << '\n' << '\n';
        cout << "        You're not going to win me" << '\n' << '\n';
        colorCyan();
        cout << "Who start 1: computer or 2: user" << '\n';
        cout << "Option 1/2: ";
        colorRed();
        cin >> option;
    } while(option<1 || option>2);

    game(option);
    menu();
}

void drawGame()
{
    system("cls");
    colorCyan();
    cout << "                Tic Tac Toe" << '\n' << '\n';
    cout << "        You're not going to win me" << '\n' << '\n';
    for(int i=0; i<9; i++)
    {
        cout << " ";
        colorPick(board[i]);
        cout << " ";
        if((i+1)%3==0 && i!=8)colorBlue(), cout << '\n' << "----------" << '\n';
        else if(i!=8)colorBlue(), cout << '|';
    }
    cout << "\n\n";
    for(int i=0; i<moveN; i++)
    {
        if(moves[i][0]=='C')colorCyan();
        else colorRed();
        cout << moves[i] << endl;
    }
}

void game(int option)
{
    int turn = option;
    int ganador;
    while(true)
    {
        drawGame();
        ganador=Win();
        if(ganador != 0)
        {
            colorYellow();
            if(ganador==1) cout << "\n\nYou Lose!\n\n";
            else cout << "\n\nYou Win!\n\n";
            break;
        }
        ganador = Tie();
        if(ganador==1)
        {
            colorYellow();
            cout << "\n\nTie\n\n";
            break;
        }
        if(turn == 1)
        {
            int move, res=-10, tmp;
            for(int i=0; i<9; i++)
            {
                if(board[i]==i+'1')
                {
                    board[i]='X';
                    tmp = computerPlay('X', 0);
                    board[i]= i+'1';
                    if(tmp>res)
                    {
                        res=tmp;
                        move=i;
                    }
                }
            }
            board[move]='X';
            turn=2;
            move++;
            moves[moveN++]="Computer move: " + to_string(move);
        }
        else if(turn == 2)
        {
            do {
                colorWhite();
                cout << "\nEnter your move: ";
                int move;
                colorRed();
                cin >> move;
                if(board[move-1] == move+'0')
                {
                    board[move-1] = 'O';
                    turn = 1;
                    moves[moveN++]="User move: " + to_string(move);
                }
                else
                {
                    colorError();
                    cout << "ERROR: Box not available\n\n";
                    turn=2;
                }
            } while(turn==2);
        }
    }
    colorWhite();
    system("pause");
}

int computerPlay(char turn, int depth)
{
    int move, minmax;

    if(Win()!=0)return (Win()*10)-depth;
    if(Tie()==1)return 0-depth;

    if(turn=='X')turn='O';
    else turn='X';

    if(turn=='O')minmax=10-depth;
    else minmax=-10-depth;


    for(int i=0; i<9; i++)
    {
        if(board[i] == i+'1')
        {
            board[i]=turn;
            move = computerPlay(turn, depth+1);
            board[i] = i+'1';
            if (((turn == 'O') && (move < minmax)) || ((turn == 'X') && (move > minmax))) minmax = move;
        }
    }
    return minmax;
}

int Win()
{
    if(board[0]==board[1] && board[1]==board[2])
        if(board[0]=='X')return 1;
        else if(board[0]=='O')return -1;

    if(board[3]==board[4] && board[4]==board[5])
        if(board[3]=='X')return 1;
        else if(board[3]=='O')return -1;

    if(board[6]==board[7] && board[7]==board[8])
        if(board[6]=='X')return 1;
        else if(board[6]=='O')return -1;

    if(board[0]==board[3] && board[3]==board[6])
        if(board[0]=='X')return 1;
        else if(board[0]=='O')return -1;

    if(board[1]==board[4] && board[4]==board[7])
        if(board[1]=='X')return 1;
        else if(board[1]=='O')return -1;

    if(board[2]==board[5] && board[5]==board[8])
        if(board[2]=='X')return 1;
        else if(board[2]=='O')return -1;

    if(board[0]==board[4] && board[4]==board[8])
        if(board[0]=='X')return 1;
        else if(board[0]=='O')return -1;

    if(board[2]==board[4] && board[4]==board[6])
        if(board[2]=='X')return 1;
        else if(board[2]=='O')return -1;

    return 0;
}

int Tie()
{
    for(int i='1'; i<='9'; i++)if(board[i-'1']==i)return 0;
    return 1;
}
