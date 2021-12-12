#include "maze.h"
int Rank;

int main()
{
    srand((unsigned)time(NULL));				// 设置随机种子
    int maze[L + 2][L + 2] = { {0},{0} };//1-L为迷宫（1、L是墙），0、L+1是边界
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
                cout << " ▓";
            else if (found[i][j]==OUT)
                cout << " *";
            else if (maze[i][j] == MAN)
                cout << "♀";
            else
                cout << "  ";
        }
        cout << endl;
    }
}

int Move(int maze[L + 2][L + 2],int found[L+2][L+2], int x,int y)
{
    fflush(stdin);//多次使用getchar需要清空stdin，pause按任意键继续，这时会读入一个字符，所以也要清空
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
        if (MessageBox(GetHWnd(), _T("您要寻求帮助吗？"), _T("询问"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
        return 1;
    default:
        printf("请输入w，a，s，d");
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
        cout << "恭喜您已经走出迷宫";
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
    cout << "☆-(> 。☆) 欢迎来到迷宫游戏 (☆。<)-☆";
    CursorGoto(39, 12);
    cout << " $$$$$$$$$$$----游戏规则----$$$$$$$$$$$";
    CursorGoto(39, 14);
    cout << "a:向左移动\td:向右移动";
    CursorGoto(39, 16);
    cout << "w:向上移动\ts:向下移动";
    CursorGoto(39, 18);
    cout << "按回车结束输入";    
    CursorGoto(39, 20);
    cout << "悄悄告诉你~实在走不出去可以按h寻求帮助哟\(^ -^)/";
    system("pause");
    system("cls");
    system("color F6");
    CursorGoto(39, 12);
    cout << "Fight!!☆( ^ -^)~''☆";
    CursorGoto(39, 16);
    cout<<"请问你喜欢离散型的还是曲折型的迷宫呢~";
    CursorGoto(39, 18);
    cout << "曲折型请按1，离散型请按2";
    CursorGoto(39, 20);
    cin >> Rank;//偷懒省略输入检查
    return Rank;
}

void CursorGoto(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


