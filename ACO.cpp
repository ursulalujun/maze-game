#include "maze.h"

#define CLOCK_PER_SEC ((clock_t)1000)

//maze[i][j] �ı��Ϊ (i - 1) * L + j;
//DFS���ɵ��Թ��Ļ�·ֻ��һ�������볤����Ϊ�ظ�����
//��ô���ӻ���
//������Ϣ������ڵľ��룬ֱ�߾��룿

const int antNum = L*10;     //����������10���Թ��߳���
const int pathNum = L * L * 2;//����ÿһ�ֵ����ǰ������
const double pVol = 0.3;   //��Ϣ�ػӷ�ϵ�� 0.2~0.5
const double pQ = 10;         //��Ϣ��ǿ�� 10~1000
const double pImp = 3;     //��Ϣ�������Ҫ�� 1~4
const double qImp = 4;     //������Ϣ�����Ҫ�� 3~4.5
const int gen = 20;       //�������� 100~500

struct ant                 //���Ͻṹ��
{
	int locx, locy;             //λ��
	int antPath[L + 2][L + 2];  //��¼ÿֻ���ϰ�ÿ���ط����˼���
	int lenPath;
	bool flag;             //�Ƿ񵽴��յ�7
};
struct ant ants[antNum];   //��Ⱥ

//Ϊ����ֱ�������Թ�����Ϣ������������������Թ�һ��
double pher[L+2][L+2];//��Ϣ�ؾ���
double nextPher[L+2][L+2];//��һ����Ϣ�ؾ���
double insp[L+2][L+2];//������Ϣ����

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
		ants[i].locx = 2;//�����㶼�����
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
				double d1 = pow(pow(x, 2) + pow(y, 2), 0.5);//����ڵľ���
				double d2 = pow(pow((j-2), 2) + pow((i-2), 2), 0.5);//����ڵľ���
				insp[i][j] = d2/(d1+0.1);//������ϢΪ����ĵ���,Ϊ�����ĸΪ0��+1
				pher[i][j] = 1;             //��Ϣ��Ũ�ȳ�ʼֵΪ1
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
	
	//���㵽ÿ������ĸ��ʺ͸��ʺ�
	for (int i = 0;i < 4;i++)
	{
		int x2 = x + direction[i][0];
		int y2 = y + direction[i][1];
		//����ǽ����ûԽ��
		if (maze[x2][y2]!=WALL && x2 > 1 && x2 < L && y2 > 1 && y2 < L)
		{
			//�߹��ܶ�ε�·�������ظ���
			if (ants[k].antPath[x2][y2])
				prob[i] = (pow(pher[x2][y2], pImp) + pow(insp[x2][y2], qImp)) / ants[k].antPath[x2][y2];
			else
				prob[i] = pow(pher[x2][y2], pImp) + pow(insp[x2][y2], qImp);		
			sum += prob[i];
		}
	}
	
	//��һ������
	for (int i = 0;i < 4;i++)
	{
		if (prob[i] > 0)
			prob[i] /= sum;
	}
	//���������ģ�����
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
				//�����ص����޸ı�־�������ߵ�·������
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
		if (ants[k].flag == 1)  //ֻ�Ե���Ŀ�ĵ������ ���߹�·�� ������Ϣ��
			for(int i=1;i<L+1;i++)
				for (int j = 1;j < L + 1;j++)
				{
					//ֻ�߹�һ�κܿ����Ǳؾ�֮·���߹���ο��ܾ����۷���
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
	int g = 0; //��ǰ����

	while (g < gen)
	{
		//1����Ⱥ���������϶�����Ŀ�ĵ�
		int p = 0; //��Ⱥǰ������
		
		while (p < pathNum)
		{
			int cntFlag = 0;
			for (int i = 0; i < antNum; i++)
			{
				if (ants[i].flag == 1)//����Ŀ�ĵ�
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
			cout << "�ﵽ��ߵ�������!" << endl;
			foundBestPath(found);
		}

		//3��������Ϣ�ؾ���
		updatePher();

		//4����ʼ����Ⱥ��������Ϣ�ؾ���
		initAnts();
		g++;
	}
	
}

void ACO(int maze[L + 2][L + 2], int found[L + 2][L + 2])
{
	//��ʼ������
	initAnts();
	initMarix(maze);
	evolution(maze,found);
}


