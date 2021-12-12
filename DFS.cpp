#include "maze.h"
int direction[4][2] = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
int Exit = 0;

void depthMaze(int maze[L + 2][L + 2], int found[L + 2][L + 2])
{
    int used[L + 2][L + 2] = { {0},{0} };
    int isfound = 0;
    initDepthMaze(maze, used, found);
    //��������һ������
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
//��ʼ����һ���ո��Ա��Ķ�ǽ��ǽ��·����������
//used��ʾ�Ƿ񱻷��ʣ���0��ʾû�У�1��ʾ��
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
    //����Ȧ��ʼ��ΪROUTE����������ǽ���ᱻ�俪
    for (i = 0;i <= L + 1;i++)
    {
        maze[0][i] = ROUTE;used[0][i] = 1;found[0][i] = 1;
        maze[i][0] = ROUTE;used[i][0] = 1;found[i][0] = 1;
        maze[i][L + 1] = ROUTE;used[i][L + 1] = 1;found[i][L + 1] = 1;
        maze[L + 1][i] = ROUTE;used[L + 1][i] = 1;found[L + 1][i] = 1;
    }
    //����������ҵĳ�ʼλ��
    maze[2][1] = MAN;
}

/*
* ���������������ֻҪ��һ����������ͨ�������ߣ�������˻���
�����������Թ��ˣ��ܷ��ʵ��ʹ������ߵ�
��������ROUTE������ͨ�ģ��Ҳ��γɻ������ں����֮���·һ��Ψһ
������������һ����ROUTE�ĵط�Ϊ����
1.��ʼ���Թ�Ϊǽ��ȫ������״̬����һ������Χ�Ķ�ǽ��������������յ�
2.���ѡһ����������û���ʹ����俪ǽ����
3.���з������ڵĶ����ʹ����˻�������ô�ж����з��򶼷��ʹ�?��
4.�˻������ֹ��
*/
void createDepthMaze(int maze[L + 2][L + 2], int used[L + 2][L + 2], int x, int y)
{
    used[x][y] = 1;
    int r = rand() % 4;
    //����Ӧ�������з�������ڸ��Ӷ����ʹ���ֹͣ���������������е㸴��
    //���Ծ��ý϶�Σ�����ܰ����з������������
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

//���ѣ��ҵ�OUT֮���������µ�·��ֻ��ǻ���·�ϵĵ�
//�ڵݹ麯��������isfound��ֵ����¼��û�ҵ������ǲ��е�
//��Ϊ���ݵ�ʱ��������ϼ�������isfound����û�ҵ���״̬
//ֻ�ܴ�ָ�룬ָ��ָ��ĵط��ǹ̶��ģ�ÿ���������涼һ��
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