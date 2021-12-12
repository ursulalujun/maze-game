#pragma once
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include<Windows.h>
#include <time.h>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>

using namespace std;

#define L 15                            //迷宫的边长
#define ROUTE 0                         //墙
#define WALL  1                         //和路径的标识
#define IN 0                            //标记入口
#define OUT 3                           //标记出口和走出迷宫的路
#define MAN 4                           //小人标识

extern int Exit;
extern int direction[4][2];
//如果不extern声明外部变量就会出现重定义问题，只能声明，不能定义（赋初值）

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


