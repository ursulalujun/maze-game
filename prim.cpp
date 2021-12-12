#include "maze.h"

void initPrimMaze(int maze[L + 2][L + 2], int set[L + 2][L + 2], int found[L+2][L+2])
{
    int i, j;
    for (i = 1;i <= L;i++)
        for (j = 1;j <= L;j++)
        {
            if (i % 2 || j % 2)
                maze[i][j] = WALL;
            else
                maze[i][j] = ROUTE;
            //set[i][j]的值要与标号之间建立一一映射
            set[i][j] = (i - 1) * L + j;
        }
    //设置起点和玩家的初始位置
    maze[2][1] = MAN;
}

/*
Prim
1.初始化迷宫全部为墙壁，随机设置起点和终点
2.随机挖洞
3.判断起点和终点之间是否连成通路
把打通的点放在一个集合中，检查四周有没有和别的点联通，合并联通的点的集合
4.不连成通路则再挖洞，否则停止
*/
void PrimMaze(int maze[L + 2][L + 2], int found[L + 2][L + 2])
{
    int set[L + 2][L + 2] = { {0},{0} }, i, j, neighborx, neighbory;
    initPrimMaze(maze, set, found);
    int randx, randy, neighRoot, randRoot;
    while (1)
    {
        //判断是否成环，是否连通，成环会影响找路的算法,2~L-1是可以被打通的
        randx = rand() % (L - 2) + 2;
        randy = rand() % (L - 2) + 2;
        if (maze[randx][randy] != ROUTE)
        {
            maze[randx][randy] = ROUTE;
            for (i = 0;i < 4;i++)
            {
                neighborx = randx + direction[i][0];
                neighbory = randy + direction[i][1];
                if (maze[neighborx][neighbory] == ROUTE)
                {
                    unionSet(set, set[randx][randy], set[neighborx][neighbory]);
                }
            }
            int rootIn = findRoot(set, set[2][2]);
            int rootOut = findRoot(set, set[L-3][L - 1]);
            //一点小问题会耽误你大量的调试时间！！！这里把maze写成了set
            if (maze[L-3][L - 1] == ROUTE && rootIn == rootOut)
            {
                 maze[L - 3][L] = OUT;break;
            }                
        }
    }
    printMaze(maze, found);   
    int help = 0;
    help = Move(maze, found, 2, 1);
    if (help)
        findPrim(maze, found, set);
}

int findRoot(int set[L + 2][L + 2], int a)
{
    int i, j;
    j = a % L;
    i = a / L + 1;
    if (set[i][j] == a)
        return a;
    else
        set[i][j]=findRoot(set, set[i][j]);//路径压缩 
    //在findRoot后面加set[i][j]=a是不行的，虽然函数的返回值是根节点的id，但是此时函数中的a不是这个返回值 
}

void unionSet(int set[L + 2][L + 2], int a, int b)
{
    int rootA, rootB;
    rootA = findRoot(set, a);
    rootB = findRoot(set, b);
    if ( rootA != rootB )
    {
        int i, j;
        j = rootA % L;
        i = rootA / L + 1;
        set[i][j] = rootB;
    }
}


void findPrim(int maze[L + 2][L + 2], int found[L + 2][L + 2], int set[L + 2][L + 2])
{
    int i, j;
    int InRoot = findRoot(set, set[2][2]);
    for(i=2;i<L;i++)
        for (j = 2;j < L;j++)
        {
            if (findRoot(set, set[i][j]) == InRoot)
                found[i][j] = OUT;
        }
    printMaze(maze, found);
}

/*
int isLoop=0, isConnected[4] = { 0 };
if (maze[randx][randy] != ROUTE)
{
    maze[randx][randy] = ROUTE;
    for (i = 0;i < 4;i++)
    {
        neighborx = randx + direction[i][0];
        neighbory = randy + direction[i][1];
        if (neighborx <= 1 || neighborx >= L || neighbory <= 1 || neighbory >= L)
            continue;
        randRoot = findRoot(set, set[randx][randy]);
        if (maze[neighborx][neighbory] == ROUTE)
        {
            neighRoot = findRoot(set, set[neighborx][neighbory]);


            if (randRoot == neighRoot)
            {
                isLoop = 1;break;
            }
            else
                isConnected[i] = 1;

        }
    }
    //必须保证不形成环才能做合并和打通

    if (!isLoop)
    {
        for (i = 0;i < 4;i++)
        {
            if (isConnected[i])
            {
                neighborx = randx + direction[i][0];
                neighbory = randy + direction[i][1];
                unionSet(set, set[randx][randy], set[neighborx][neighbory]);
            }
        }
        maze[randx][randy] = ROUTE;
        for (j = 2;j <= L - 1;j++)
        {
            if (set[j][L - 1] == ROUTE&& findRoot(set, set[2][2]) == findRoot(set, set[j][L - 1]))
            {
                t = 0;
            }
            maze[j][L] = ROUTE;
        }
    }

    int rootIn = findRoot(set, set[2][2]);
    for (j = 2;j <= L - 1;j++)
    {
        int rootOut = findRoot(set, set[j][L - 1]);
        //一点小问题会耽误你大量的调试时间！！！这里把maze写成了set
        if (maze[j][L - 1] == ROUTE && rootIn == rootOut)
        {
            t = 0;
            maze[j][L] = OUT;break;
        }
    }
}
*/