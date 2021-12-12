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
            //set[i][j]��ֵҪ����֮�佨��һһӳ��
            set[i][j] = (i - 1) * L + j;
        }
    //����������ҵĳ�ʼλ��
    maze[2][1] = MAN;
}

/*
Prim
1.��ʼ���Թ�ȫ��Ϊǽ�ڣ�������������յ�
2.����ڶ�
3.�ж������յ�֮���Ƿ�����ͨ·
�Ѵ�ͨ�ĵ����һ�������У����������û�кͱ�ĵ���ͨ���ϲ���ͨ�ĵ�ļ���
4.������ͨ·�����ڶ�������ֹͣ
*/
void PrimMaze(int maze[L + 2][L + 2], int found[L + 2][L + 2])
{
    int set[L + 2][L + 2] = { {0},{0} }, i, j, neighborx, neighbory;
    initPrimMaze(maze, set, found);
    int randx, randy, neighRoot, randRoot;
    while (1)
    {
        //�ж��Ƿ�ɻ����Ƿ���ͨ���ɻ���Ӱ����·���㷨,2~L-1�ǿ��Ա���ͨ��
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
            //һ��С����ᵢ��������ĵ���ʱ�䣡���������mazeд����set
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
        set[i][j]=findRoot(set, set[i][j]);//·��ѹ�� 
    //��findRoot�����set[i][j]=a�ǲ��еģ���Ȼ�����ķ���ֵ�Ǹ��ڵ��id�����Ǵ�ʱ�����е�a�����������ֵ 
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
    //���뱣֤���γɻ��������ϲ��ʹ�ͨ

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
        //һ��С����ᵢ��������ĵ���ʱ�䣡���������mazeд����set
        if (maze[j][L - 1] == ROUTE && rootIn == rootOut)
        {
            t = 0;
            maze[j][L] = OUT;break;
        }
    }
}
*/