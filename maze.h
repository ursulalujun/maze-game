#pragma once
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include<Windows.h>
#include <time.h>
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>

using namespace std;

#define L 15                            //�Թ��ı߳�
#define ROUTE 0                         //ǽ
#define WALL  1                         //��·���ı�ʶ
#define IN 0                            //������
#define OUT 3                           //��ǳ��ں��߳��Թ���·
#define MAN 4                           //С�˱�ʶ

extern int Exit;
extern int direction[4][2];
//�����extern�����ⲿ�����ͻ�����ض������⣬ֻ�����������ܶ��壨����ֵ��

//DFS
void depthMaze(int maze[L + 2][L + 2], int found[L + 2][L + 2]);
void initDepthMaze(int maze[L + 2][L + 2], int used[L + 2][L + 2], int found[L + 2][L + 2]);
void createDepthMaze(int maze[L + 2][L + 2], int used[L + 2][L + 2], int x, int y);
void findDFS(int maze[L + 2][L + 2], int found[L + 2][L + 2], int x, int y, int* isfound);

//Prim
int findRoot(int set[L + 2][L + 2], int a);
void unionSet(int set[L + 2][L + 2], int a, int b);
void initPrimMaze(int maze[L + 2][L + 2], int set[L + 2][L + 2], int found[L + 2][L + 2]);
void PrimMaze(int maze[L + 2][L + 2], int found[L + 2][L + 2]);
void findPrim(int maze[L + 2][L + 2], int found[L + 2][L + 2], int set[L + 2][L + 2]);

int HomeScreen();
void CursorGoto(int x, int y);
void printMaze(int maze[L + 2][L + 2], int found[L + 2][L + 2]);
//void findPath(int maze[L + 2][L + 2], int found[L + 2][L + 2], int x, int y, int* isfound);
int Move(int maze[L + 2][L + 2], int found[L + 2][L + 2], int x, int y);

//ACO
void ACO(int maze[L + 2][L + 2], int found[L + 2][L + 2]);
void initAnts();
void initMarix(int maze[L + 2][L + 2]);
void updateAnt(int k, int xNext, int yNext);
void dirSelect(int k, int maze[L + 2][L + 2]);
void getAntLen(int k);
void foundBestPath(int found[L + 2][L + 2]);
void updatePher();
void evolution(int maze[L + 2][L + 2], int found[L + 2][L + 2]);


