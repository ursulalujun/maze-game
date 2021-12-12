#include "maze.h"

#define CLOCK_PER_SEC ((clock_t)1000)

//maze[i][j] 的标号为 (i - 1) * L + j;
//DFS生成的迷宫的活路只有一条，距离长是因为重复走了
//怎么可视化？
//启发信息，离出口的距离，直线距离？

const int antNum = L*10;     //蚂蚁数量（10倍迷宫边长）
const int pathNum = L * L * 2;//蚂蚁每一轮的最大前进步数
const double pVol = 0.3;   //信息素挥发系数 0.2~0.5
const double pQ = 10;         //信息素强度 10~1000
const double pImp = 3;     //信息素相对重要性 1~4
const double qImp = 4;     //启发信息相对重要性 3~4.5
const int gen = 20;       //迭代次数 100~500

struct ant                 //蚂蚁结构体
{
	int locx, locy;             //位置
	int antPath[L + 2][L + 2];  //记录每只蚂蚁把每个地方走了几遍
	int lenPath;
	bool flag;             //是否到达终点7
};
struct ant ants[antNum];   //蚁群

//为了能直接利用迷宫的信息，其他数组的索引与迷宫一致
double pher[L+2][L+2];//信息素矩阵
double nextPher[L+2][L+2];//下一代信息素矩阵
double insp[L+2][L+2];//启发信息矩阵

clock_t start, finish;
double duration;

void initAnts()
{
	for (int k = 0; k < antNum; k++)
	{
		for (int i = 0;i < L+2; i++)
		{
			for(int j=0;j<L+2;j++)
				ants[k].antPath[i][j] = 0;			
		}
		ants[k].lenPath = 10000;
	}
	for (int i = 0; i < antNum; i++)
	{
		ants[i].locx = 2;//出发点都在起点
		ants[i].locy = 2;
		ants[i].antPath[2][2] = 1;
		ants[i].flag = 0;
	}
}

void initMarix(int maze[L + 2][L + 2])
{
	for (int i = 0;i < L + 2;i++)
	{
		for (int j = 0;j < L + 2;j++)
		{
			pher[i][j] = 0;
			nextPher[i][j] = 0;
			insp[i][j] = 0;
			if (maze[i][j] != WALL)
			{
				int x = L - j, y = Exit - i;
				double d1 = pow(pow(x, 2) + pow(y, 2), 0.5);//离出口的距离
				double d2 = pow(pow((j-2), 2) + pow((i-2), 2), 0.5);//离入口的距离
				insp[i][j] = d2/(d1+0.1);//启发信息为距离的倒数,为避免分母为0，+1
				pher[i][j] = 1;             //信息素浓度初始值为1
			}
		}
	}
}

void updateAnt(int k, int xNext, int yNext)
{
	ants[k].locx = xNext;
	ants[k].locy = yNext;
	ants[k].antPath[xNext][yNext] += 1;
}

void dirSelect(int k, int maze[L+2][L+2])
{
	double sum=0, max=-1000;
	double prob[4] = { -1, -1, -1, -1 };
	int xNext, yNext;
	int x = ants[k].locx;
	int y = ants[k].locy;
	
	//计算到每个方向的概率和概率和
	for (int i = 0;i < 4;i++)
	{
		int x2 = x + direction[i][0];
		int y2 = y + direction[i][1];
		//不是墙，且没越界
		if (maze[x2][y2]!=WALL && x2 > 1 && x2 < L && y2 > 1 && y2 < L)
		{
			//走过很多次的路尽量不重复走
			if (ants[k].antPath[x2][y2])
				prob[i] = (pow(pher[x2][y2], pImp) + pow(insp[x2][y2], qImp)) / ants[k].antPath[x2][y2];
			else
				prob[i] = pow(pher[x2][y2], pImp) + pow(insp[x2][y2], qImp);		
			sum += prob[i];
		}
	}
	
	//归一化概率
	for (int i = 0;i < 4;i++)
	{
		if (prob[i] > 0)
			prob[i] /= sum;
	}
	//产生随机数模拟赌盘
	while (1)
	{
		double r1 = rand() / double(RAND_MAX);
		int r2 = rand() % 4;
		if (r1 <= prob[r2])
		{
			xNext = x + direction[r2][0];
			yNext = y + direction[r2][1];
			updateAnt(k, xNext, yNext);
			if (xNext == Exit && yNext == (L-1))
			{
				//到达重点则修改标志，计算走的路径长度
				ants[k].flag = 1;
				getAntLen(k);
			}
			break;
		}			
	}	
}

void getAntLen(int k)
{
	int len = 0;
	for (int i = 1;i < L + 1;i++)
		for (int j = 1;j < L + 1;j++)
		{
			if(ants[k].antPath[i][j])
				len ++ ;
		}
	ants[k].lenPath = len;
}

void foundBestPath(int found[L + 2][L + 2])
{
	int bestAnt = 0;
	for (int k = 0; k < antNum; k++)
	{
		if (ants[k].lenPath < ants[bestAnt].lenPath)
			bestAnt = k;
	}
	for (int i = 1;i < L + 1;i++)
		for (int j = 1;j < L + 1;j++)
		{
			//if (ants[bestAnt].antPath[i][j]>0&& ants[bestAnt].antPath[i][j]<3)
			if (ants[bestAnt].antPath[i][j])
				found[i][j] = OUT;
		}
}

void updatePher()
{
	for (int k = 0; k < antNum; k++)
	{
		if (ants[k].flag == 1)  //只对到达目的点的蚂蚁 所走过路径 更新信息素
			for(int i=1;i<L+1;i++)
				for (int j = 1;j < L + 1;j++)
				{
					//只走过一次很可能是必经之路，走过多次可能就是折返了
					if (ants[k].antPath[i][j])
						nextPher[i][j] += pQ / (ants[k].lenPath * ants[k].antPath[i][j]);
				}
	}
	for (int i = 1;i < L + 1;i++)
		for (int j = 1;j < L + 1;j++)
		{
			pher[i][j] = pVol * pher[i][j] + nextPher[i][j];
			nextPher[i][j] = 0;
		}
}

void evolution(int maze[L + 2][L + 2], int found[L + 2][L + 2])
{
	int g = 0; //当前代数

	while (g < gen)
	{
		//1、蚁群内所有蚂蚁都到达目的地
		int p = 0; //蚁群前进步数
		
		while (p < pathNum)
		{
			int cntFlag = 0;
			for (int i = 0; i < antNum; i++)
			{
				if (ants[i].flag == 1)//到达目的地
				{
					cntFlag++;continue;
				}				
				dirSelect(i, maze);
			}
			if (cntFlag == antNum) break;
			p++;
		}

		if (g == gen - 1)
		{
			cout << "达到最高迭代次数!" << endl;
			foundBestPath(found);
		}

		//3、更新信息素矩阵
		updatePher();

		//4、初始化蚁群；更新信息素矩阵
		initAnts();
		g++;
	}
	
}

void ACO(int maze[L + 2][L + 2], int found[L + 2][L + 2])
{
	//初始化参数
	initAnts();
	initMarix(maze);
	evolution(maze,found);
}


