#include "maze.h"
int Rank;

int main()
{
    srand((unsigned)time(NULL));				// �����������
    int maze[L + 2][L + 2] = { {0},{0} };//1-LΪ�Թ���1��L��ǽ����0��L+1�Ǳ߽�
    int used[L + 2][L + 2] = { {0},{0} };
    int found[L + 2][L + 2] = { {0},{0} };
    int isfound = 0, rank = 0;
    rank=HomeScreen();
    switch (rank)
    {
    case 1:
        depthMaze(maze, found);
        break;
    case 2:
        PrimMaze(maze, found);
        break;
    default:
        break;
    }  
}

void printMaze(int maze[L + 2][L + 2], int found[L + 2][L + 2])
{
    system("cls");
    system("color F4");
    int i, j;
    for (i = 1;i <= L;i++)
    {
        for (j = 1;j <= L;j++)
        {
            if (maze[i][j] == WALL)
                cout << " ��";
            else if (found[i][j]==OUT)
                cout << " *";
            else if (maze[i][j] == MAN)
                cout << "��";
            else
                cout << "  ";
        }
        cout << endl;
    }
}

int Move(int maze[L + 2][L + 2],int found[L+2][L+2], int x,int y)
{
    fflush(stdin);//���ʹ��getchar��Ҫ���stdin��pause���������������ʱ�����һ���ַ�������ҲҪ���
    char m;
    enum dire { down, up, right, left };
    dire temp;
    m = getchar();
    if (m == '\n')
        m = getchar();
    fflush(stdin);
    switch (m)
    {
    case 'a':
        temp = left;break;
    case 'w':
        temp = up;break;
    case 's':
        temp = down;break;
    case 'd':
        temp = right;break;
    case 'h':
        if (MessageBox(GetHWnd(), _T("��ҪѰ�������"), _T("ѯ��"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
        return 1;
    default:
        printf("������w��a��s��d");
        Move(maze, found, x, y);break;
    }
    int x2 = x + direction[temp][0];
    int y2 = y + direction[temp][1];
    if (maze[x2][y2] == WALL)
        Move(maze, found, x, y);
    else
    {
        maze[x][y] = ROUTE;
        maze[x2][y2] = MAN;
        printMaze(maze, found);
    }
    if (maze[x2][y2] == OUT)
    {
        cout << "��ϲ���Ѿ��߳��Թ�";
        return 0;
    }        
    else
        Move(maze, found, x2, y2);
}

int HomeScreen()
{
    system("cls");
    system("color F2");
    CursorGoto(39, 10);
    cout << "��-(> ����) ��ӭ�����Թ���Ϸ (�<)-��";
    CursorGoto(39, 12);
    cout << " $$$$$$$$$$$----��Ϸ����----$$$$$$$$$$$";
    CursorGoto(39, 14);
    cout << "a:�����ƶ�\td:�����ƶ�";
    CursorGoto(39, 16);
    cout << "w:�����ƶ�\ts:�����ƶ�";
    CursorGoto(39, 18);
    cout << "���س���������";    
    CursorGoto(39, 20);
    cout << "���ĸ�����~ʵ���߲���ȥ���԰�hѰ�����Ӵ\(^ -^)/";
    system("pause");
    system("cls");
    system("color F6");
    CursorGoto(39, 12);
    cout << "Fight!!��( ^ -^)~''��";
    CursorGoto(39, 16);
    cout<<"������ϲ����ɢ�͵Ļ��������͵��Թ���~";
    CursorGoto(39, 18);
    cout << "�������밴1����ɢ���밴2";
    CursorGoto(39, 20);
    cin >> Rank;//͵��ʡ��������
    return Rank;
}

void CursorGoto(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


