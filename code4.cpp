#include <stdio.h>  
#include <stdlib.h>  
#include <time.h> 
#include<conio.h>
#include<Windows.h>
#include "stack.h"
typedef struct{
	int x;
	int y;
}position;

//建立存储迷宫的栈函数结构体
typedef struct
{
	int maze[10][10];
	position pos;//用于存储人物当前位置
}Maze;
typedef struct
{
	Maze* bottom;
	Maze* top;
}Stack;

Stack* StackCreate();
void StackFree(Stack* stack);
void StackPush(Stack* stack, Maze maze);
Maze StackPop(Stack* stack);


//决策树操作
typedef struct TreeNode{
	char ch;
	struct TreeNode* LChild;
	struct TreeNode* RChild;
}*tree, BinTree;

BinTree* CreateBinTree();
void preorderTraversal(BinTree* root, Stack* stack);
void Game(Stack* stack);




void mazegenerator(int maze[10][10]); //生成迷宫函数
void display(int maze[10][10], position pos);//打印迷宫函数
void PlayGame(int maze[10][10], position pos);
int pass(int maze[10][10], int x, int y);
void Game();
int main()
{
	position pos;
	pos.x = 1;
	pos.y = 1;
	int maze[10][10];
	srand((unsigned)time(NULL));
	mazegenerator(maze);
	STACK stack;
	stackInit(&stack);
	while (mizePath(maze, &stack, 3, 3) == 0){
		mazegenerator(maze);
		maze[3][3] = 0;
		stackInit(&stack);
	}

	printf("maze:\n");
	display(maze, pos);
	PlayGame(maze, pos);
}

void mazegenerator(int maze[10][10]){
	srand((unsigned)time(NULL));
	for (int i = 0; i<10; i++){
		for (int j = 0; j<10; j++){
			int x = rand();
			if (x % 2 == 0){
				maze[i][j] = 1;
			}
			else{
				maze[i][j] = 0;
			}
		}
	}
}
void display(int maze[10][10], position pos){

	for (int i = 0; i<12; i++){
		printf("□");
	}
	printf("\n");
	for (int i = 0; i<10; i++){
		printf("□");
		for (int j = 0; j<10; j++){
			if (i == pos.x&&j == pos.y){
				printf("○");
			}
			else{

				if (maze[i][j] == 1)
				{
					printf("■");
				}
				else
				{
					printf("□");
				}
			}
		}
		printf("□");
		printf("\n");
	}
	for (int i = 0; i<12; i++){
		printf("□");
	}
	printf("\n");
}
void PlayGame(int maze[10][10], position pos){
	Stack* stack = StackCreate();
	Maze m;
	while (1)
	{
		char ch = _getch();
		switch (ch)
		{
		case 'w':
			if (pass(maze, pos.x - 1, pos.y)){
				pos.x--;
				m.pos = pos;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						m.maze[i][j] = maze[i][j];
					}
				}
				StackPush(stack, m);
				system("cls");
				srand((unsigned)time(NULL));
				int x = rand();
				if (x % 2 == 0)
				{
					//进入空间
					Game(stack);
					printf("\n");
					display((stack->top - 1)->maze, (stack->top - 1)->pos);
				}
				else
				{
					display(maze, pos);
				}
				StackPop(stack);
			}
			break;
		case 's':
			if (pass(maze, pos.x + 1, pos.y)){
				pos.x++;
				m.pos = pos;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						m.maze[i][j] = maze[i][j];
					}
				}
				StackPush(stack, m);
				system("cls");
				srand((unsigned)time(NULL));
				int x = rand();
				if (x % 2 == 0)
				{
					//进入空间
					Game(stack);
					printf("\n");
					display((stack->top - 1)->maze, (stack->top - 1)->pos);
				}
				else
				{
					display(maze, pos);
				}
				StackPop(stack);
			}
			break;
		case 'a':
			if (pass(maze, pos.x, pos.y - 1)){
				pos.y--;
				m.pos = pos;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						m.maze[i][j] = maze[i][j];
					}
				}
				system("cls");
				StackPush(stack, m);
				srand((unsigned)time(NULL));
				int x = rand();
				if (x % 2 == 0)
				{

					//进入空间
					Game(stack);
					printf("\n");
					display((stack->top - 1)->maze, (stack->top - 1)->pos);
				}
				else
				{
					display(maze, pos);
				}
				StackPop(stack);

			}
			break;
		case 'd':
			if (pass(maze, pos.x, pos.y + 1)){
				pos.y++;
				m.pos = pos;
				for (int i = 0; i < 10; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						m.maze[i][j] = maze[i][j];
					}
				}
				StackPush(stack, m);
				system("cls");
				srand((unsigned)time(NULL));
				int x = rand();
				if (x % 2 == 0)
				{
					//进入空间
					Game(stack);
					printf("\n");
					display((stack->top - 1)->maze, (stack->top - 1)->pos);
				}
				else
				{
					display(maze, pos);
				}
				StackPop(stack);
			}
			break;
		default:
			printf("输入错误");
			break;
		}
		if (pos.x == 5 && pos.y == 5)
		{
			printf("你已经出迷宫");
			break;
		}
	}
}
int pass(int maze[10][10], int x, int y){
	if (maze[x][y] == 1){
		return 0;
	}
	else
	{
		return 1;//可以通过
	}
}
Stack* StackCreate(){
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->bottom = (Maze*)malloc(sizeof(Maze));
	if (!stack->bottom){
		perror("分配空间失败");
		exit(-1);
	}
	stack->top = stack->bottom;
	return stack;
}

void StackPush(Stack* stack, Maze maze){
	*stack->top++ = maze;
}

Maze StackPop(Stack* stack){
	stack->top--;
	return *stack->top;

}
void Game(Stack* stack){
	BinTree* root = CreateBinTree();
	preorderTraversal(root, stack);
}
BinTree* CreateBinTree(){
	BinTree* root;
	char ch;
	scanf_s("%c", &ch);
	if (ch == '#')
		root = NULL;
	else
	{
		root = (BinTree*)malloc(sizeof(BinTree));
		root->ch = ch;
		root->LChild = CreateBinTree();
		root->RChild = CreateBinTree();
	}
	return root;
}
void preorderTraversal(BinTree* root, Stack* stack){
	if (root)
	{

		switch (root->ch)
		{
		case 'r':
			printf("进入战斗\n");
			printf("\n");
			break;
		case '0':
			//回到原点
			(stack->top - 1)->pos.x = 1;
			(stack->top - 1)->pos.y = 1;
			return;
			break;
		case '1':
			//回到原来位置
			return;
			break;
		case '3':
			printf("你还剩3hp");
			printf("\n");
			break;
		default:

			break;
		}
		preorderTraversal(root->LChild, stack);
		preorderTraversal(root->RChild, stack);
	}
}
char* read(){
	FILE* fp;
	fp = fopen("D:\\game.txt", "r");//打开文件的方式
	char* p;
	int i=0;
	if (fp == NULL)
	{
		printf("不能打开文件");
		exit(1);
	}
	while (!feof(fp)){
		fscanf(fp, "%c", p+i);
		i++;
	}
	fclose(fp);
	return p;
}