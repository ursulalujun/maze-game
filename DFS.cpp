#include "maze.h"
int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
int Exit = 0;

void depthMaze(int maze[L + 2][L + 2], int found[L + 2][L + 2])
{
    int used[L + 2][L + 2] = { {0},{0} };
    int isfound = 0;
    initDepthMaze(maze, used, found);
    //任意设置一个出口
    int r = rand() % L;//2<=r<=L-1
    while (maze[r][L - 1] != ROUTE||r<2)
    {
        r = rand() % L;
    }
    maze[r][L] = OUT;
    Exit = r;
    createDepthMaze(maze, used, 2, 2);
    printMaze(maze, found);
    int help = 0;
    help = Move(maze, found, 2, 1);
    if (help)
        ACO(maze, found);
        //findDFS(maze, found, 2, 1, &isfound);
    printMaze(maze, found);
}
//初始化：一个空格旁边四堵墙，墙和路都当做网格
//used表示是否被访问，到0表示没有，1表示有
void initDepthMaze(int maze[L + 2][L + 2], int used[L + 2][L + 2], int found[L + 2][L + 2])
{
    int i, j;
    for (i = 1;i <= L;i++)
        for (j = 1;j <= L;j++)
        {
            if (i % 2 || j % 2)
                maze[i][j] = WALL;
            else
                maze[i][j] = ROUTE;
        }
    //最外圈初始化为ROUTE，让最外层的墙不会被凿开
    for (i = 0;i <= L + 1;i++)
    {
        maze[0][i] = ROUTE;used[0][i] = 1;found[0][i] = 1;
        maze[i][0] = ROUTE;used[i][0] = 1;found[i][0] = 1;
        maze[i][L + 1] = ROUTE;used[i][L + 1] = 1;found[i][L + 1] = 1;
        maze[L + 1][i] = ROUTE;used[L + 1][i] = 1;found[L + 1][i] = 1;
    }
    //设置起点和玩家的初始位置
    maze[2][1] = MAN;
}

/*
* 深度优先搜索：（只要有一个方向）能走通就往下走，否则就退回来
访问完整个迷宫了，能访问到就代表能走到
所以所有ROUTE都是连通的，且不形成环，出口和入口之间的路一定唯一
可以任意设置一个是ROUTE的地方为出口
1.初始化迷宫为墙壁全部封死状态，（一个空周围四堵墙）随机设置起点和终点
2.随机选一个方向，相邻没访问过就凿开墙访问
3.所有方向相邻的都访问过就退回来（怎么判断所有方向都访问过?）
4.退回起点终止。
*/
void createDepthMaze(int maze[L + 2][L + 2], int used[L + 2][L + 2], int x, int y)
{
    used[x][y] = 1;
    int r = rand() % 4;
    //本来应该是所有方向的相邻格子都访问过才停止，但是这样操作有点复杂
    //所以就用较多次，大概能把所有方向遍历到即可
    for (int i = 0;i < 8;i++)
    {
        int x2 = x + 2 * direction[r][0];
        int y2 = y + 2 * direction[r][1];
        if (!used[x2][y2])
        {
            maze[x + direction[r][0]][y + direction[r][1]] = ROUTE;
            createDepthMaze(maze, used, x2, y2);
        }
        r = (r + 1) % 4;
    }
    return;
}

//深搜，找到OUT之后不再搜索新的路且只标记回溯路上的点
//在递归函数里想用isfound传值来记录找没找到出口是不行的
//因为回溯的时候进入了上级函数，isfound还是没找到的状态
//只能传指针，指针指向的地方是固定的，每个函数里面都一样
void findDFS(int maze[L + 2][L + 2], int found[L + 2][L + 2], int x, int y, int* pfound)
{
    found[x][y] = 1;
    for (int i = 0;i < 4;i++)
    {
        if (*pfound)
            break;
        int x2 = x + direction[i][0];
        int y2 = y + direction[i][1];
        if (maze[x2][y2] == OUT)
        {
            *pfound = 1;
            found[x][y] = OUT;
            found[x2][y2] = OUT;
            return;
        }
        if (maze[x2][y2] == ROUTE && !found[x2][y2])
        {
            findDFS(maze, found, x2, y2, pfound);
        }
    }
    if (*pfound)
        found[x][y] = OUT;
    return;
}