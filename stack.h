#include<stdio.h>
#include<stdlib.h>
int flag[10][10] = { 0 };
typedef struct node{
	int datax;
	int datay;
	struct node* next;
}Node, *LinkList;

typedef struct stack{
	LinkList top;
}STACK;

int stackInit(STACK* s);
int pushStack(STACK* s, int x, int y);
void popStack(STACK* s, int* x, int* y);
int isStackEmpty(STACK* s);
int mizePath(int maze[10][10], STACK* s, int end_x, int end_y);  //�Թ�·������
int passMizu(int maze[10][10], int x, int y);//�ж��Ƿ�ͨ������
int printStackData(STACK s);
int stackInit(STACK* s)
{
	LinkList p = (LinkList)malloc(sizeof(Node));
	if (!p)   return -1;
	p->next = NULL;
	p->datax = -1;
	p->datay = -1;
	s->top = p;
	return 1;
}
//��ջ����  
int pushStack(STACK* s, int x, int y)
{
	LinkList p = (LinkList)malloc(sizeof(Node));
	if (!p)   return -1;  //�����ڴ�ʧ��  
	p->datax = x;
	p->datay = y;
	p->next = s->top;
	s->top = p;
	return 1;
}
//��ջ�Ĳ���  
void popStack(STACK* s, int* x, int* y)
{
	LinkList p = s->top;
	s->top = p->next;
	(*x) = p->datax;
	(*y) = p->datay;
	free(p);
}
//�ж�ջ�Ƿ�Ϊ��   
//1 ��  0 ����   
int isStackEmpty(STACK* s)
{
	if (s->top->datax == -1)  //ջ��   
		return 1;
	return 0;
}
//�ҵ����·��  
//end_x , end_yΪ����������  
//�� ���ҡ��¡���Ѱ�ҷ�ʽ   
int mizePath(int maze[10][10], STACK* s, int end_x, int end_y)
{
	pushStack(s, 1, 1); //��ʼ����ѹջ   
	int nowx = 1, nowy = 1;
	flag[nowx][nowy] = 1;  //�������Ѿ���ռ�ò�����ͨ��   
	while (!isStackEmpty(s)) //��ջ���յ�ʱ��   
	{
		if ((nowx == end_x) && (nowy == end_y))
		{
			return 1;
		}
		if (passMizu(maze, nowx, nowy - 1))   //������Ѱ��  
		{
			nowy = nowy - 1; //�������   
			pushStack(s, nowx, nowy);  //�Ѹ�����ѹջ  
			flag[nowy][nowx] = 1;  //�������Ѿ���ռ�ò�����ͨ��  
		}
		else  if (passMizu(maze, nowx + 1, nowy)) //����Ѱ��           
		{
			nowx = nowx + 1;
			pushStack(s, nowx, nowy);  //�Ѹ�����ѹջ  
			flag[nowy][nowx] = 1;  //�������Ѿ���ռ�ò�����ͨ��  
		}
		else if (passMizu(maze, nowx, nowy + 1)) //����Ѱ��   
		{
			nowy = nowy + 1;
			pushStack(s, nowx, nowy);  //�Ѹ�����ѹջ  
			flag[nowy][nowx] = 1;  //�������Ѿ���ռ�ò�����ͨ��  
		}
		else if (passMizu(maze, nowx - 1, nowy)) //����Ѱ��   
		{
			nowx = nowx - 1;
			pushStack(s, nowx, nowy);  //�Ѹ�����ѹջ  
			flag[nowy][nowx] = 1;  //�������Ѿ���ռ�ò�����ͨ��  
		}
		else  //���в�ͨ   
		{
			popStack(s, &nowx, &nowy);
		}

	} //while(!isStackEmpty(s)) //��ջ���յ�ʱ��   
	return 0;
}
//�жϸ�λ���Ƿ��ͨ   
int passMizu(int maze[10][10], int x, int y)
{
	if ((x > 9) || (y > 9))
		return 0;  //Խ�粻��ͨ  
	if (maze[y][x])
		return 0;  //��λ����ǽ������ͨ  
	if (flag[y][x])
		return 0;  //�������Ѿ���ռ�ã�����ͨ��   
	return 1;
}
//��ӡջ�е�����   
int printStackData(STACK s)
{
	STACK temp;  //�½�һ����ʱ��ջ   
	stackInit(&temp);
	if (s.top->datax == -1)  return 0; //ջΪ��   
	while (s.top->datax != -1)
	{
		pushStack(&temp, s.top->datax, s.top->datay);
		s.top = s.top->next;
	}
	while (temp.top->datax != -1)
	{
		printf("(%d,%d)\n", temp.top->datax, temp.top->datay);
		temp.top = temp.top->next;
	}
	return 1;
}