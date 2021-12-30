#include<stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define BOMBSNUM 10


void GameMenu();

void InitBoard(char Board[ROWS][COLS], int row, int col, char ch);

void SetBombs(char Bombs[ROWS][COLS], int row, int col, int Bombsnum);

void ShowBoard(char Board[ROWS][COLS], int row, int col);

int BombsAround(char Bombs[ROWS][COLS], int row, int col);

char FindBombs(char Board[ROWS][COLS], char Bombs[ROWS][COLS], int row, int col);

void Game(char Board[ROWS][COLS], char Bombs[ROWS][COLS], int row, int col);

void MoveBomb(char Bombs[ROWS][COLS], int row, int col);

void OpenMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y);

void SafeArea(char Board[ROWS][COLS], char Bombs[ROWS][COLS], int row, int col);

void GameMenu()
{
	printf("*****************************************\n");
	printf("*********      1.��ʼ��Ϸ       *********\n");
	printf("*********      0.������Ϸ       *********\n");
	printf("*****************************************\n");
}

void InitBoard(char Board[ROWS][COLS], int row, int col,char ch)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			Board[i][j] = ch;
		}
	}
}
//��ʼ��

void SetBombs(char Bombs[ROWS][COLS], int row, int col, int Bombsnum)
{
	int x, y,count=0;
	while( count < Bombsnum )
	{
		x = rand() % row+1;
		y = rand() % col+1;

		if (Bombs[x][y] != '1')
		{
			Bombs[x][y] = '1';
			count++;
		}
	}
}
//����ը��

void ShowBoard(char Board[ROWS][COLS], int row, int col)
{
	int i, j;
	printf(" ");
	for (i = 0; i < row+1; i++)
	{
		printf("%d   ",i);
	}
	printf("\n");
	for (i = 0; i < row; i++)
	{
		if (0 == i)
			printf("   |");
		else
			printf("|");
		printf("---");
	}
	printf("|\n");
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (0 == j)
			{
				printf(" ");
				printf("%d ", i + 1);
				printf("|");
			}
			printf(" %c |", Board[i+1][j+1]);
		}
		printf("\n");
		for (j = 0; j < col; j++)
		{
			if ( 0 == j )
				printf("   |");
			printf("---|");
		}
		printf("\n");
	}
}
//����

int BombsAround(char Bombs[ROWS][COLS], int row, int col)
{
	return Bombs[row - 1][col] + Bombs[row + 1][col] + Bombs[row][col - 1] + Bombs[row][col + 1] + Bombs[row + 1][col + 1] + Bombs[row - 1][col - 1] + Bombs[row + 1][col - 1] + Bombs[row - 1][col + 1] - 8 * '0';
}
//�����Χ��ը��

void MoveBomb(char Bombs[ROWS][COLS], int row, int col)
{
	Bombs[row][col] = '0';
	SetBombs(Bombs, ROW, COL, 1);
}
//��ֹ��ҵ�һ��ѡ��ʱ����ը������ը���ƶ������λ��

void SafeArea(char Board[ROWS][COLS], char Bombs[ROWS][COLS], int row, int col)
{
	int flag;
	flag = BombsAround(Bombs, row, col);
	if (0 == flag)
	{
		Board[row][col] = ' ';
		if (row - 1 > 0 && row + 1 <= ROW && col > 0 && col <= COL && Board[row - 1][col] == '*')
			SafeArea(Board, Bombs, row-1, col);
		if (row + 1 > 0 && row + 1 <= ROW && col > 0 && col <= COL && Board[row +1 ][col] == '*')
			SafeArea(Board, Bombs, row+1, col);
		if (row > 0 && row <= ROW && col - 1 > 0 && col - 1 <= COL && Board[row][col - 1] == '*')
			SafeArea(Board, Bombs, row, col-1);
		if (row > 0 && row <= ROW && col + 1 > 0 && col + 1 <= COL && Board[row][col + 1] == '*')
			SafeArea(Board, Bombs, row, col+1);
		if (row - 1 > 0 && row - 1 <= ROW && col - 1 > 0 && col - 1 <= COL && Board[row - 1][col - 1] == '*')
			SafeArea(Board, Bombs, row-1, col-1);
		if (row + 1 > 0 && row + 1 <= ROW && col + 1 > 0 && col + 1 <= COL && Board[row + 1][col + 1] == '*')
			SafeArea(Board, Bombs, row+1, col+1);
		if (row - 1 > 0 && row - 1 <= ROW && col + 1 > 0 && col + 1 <= COL && Board[row - 1][col + 1] == '*')
			SafeArea(Board, Bombs, row-1, col+1);
		if (row + 1 > 0 && row + 1 <= ROW && col - 1 > 0 && col - 1 <= COL && Board[row + 1][col - 1] == '*')
			SafeArea(Board, Bombs, row+1, col-1);
	}
	else
	{
		Board[row][col] = BombsAround(Bombs, row, col) + '0';
	}
}

int WinGame(char Board[ROWS][COLS], int row, int col)
{
	int i, j, flag=0;
	for (i=1; i < row; i++)
	{
		for (j = 1; j < col; j++)
		{
			if (Board[i][j] == '*')
				flag++;
		}
	}
	return flag;
}

char FindBombs(char Board[ROWS][COLS], char Bombs[ROWS][COLS], int row, int col)
{
	int x, y,count=1;
	while(count)
	{
		printf("�������к��У�\n");
		scanf("%d%d",&x,&y);
		system("CLS");
		if (x > 0 && x <= row && y > 0 && y <= col)
		{
			if (Bombs[x][y] == '1')
			{
				if (1 == count)
				{
					MoveBomb(Bombs, x, y);
					Board[x][y] = BombsAround(Bombs, x, y) + '0';
					SafeArea(Board, Bombs, x, y);
					count++;
				}
				else
				{
					ShowBoard(Bombs, ROW, COL);
					return 'F';
				}

			}
			else if (Board[x][y] >= '0' && Board[x][y] <= '8' && Board[x][y] != '*' && Board[x][y] != ' ')
			{
				printf("�������ѱ�����\n");
			}
			else
			{
				Board[x][y] = BombsAround(Bombs, x, y) + '0';
				SafeArea(Board, Bombs, x, y);
				count++;
				if (WinGame(Board, ROW, COL) == BOMBSNUM)
					return 'T';
				ShowBoard(Board, ROW, COL);
			}
		}
		else
		{
			printf("�����������������\n");
		}
	}
}
//�Ų�ը��

void Game(char Board[ROWS][COLS],char Bombs[ROWS][COLS], int row, int col)
{
	char flag;
	InitBoard(Board, ROWS, COLS, '*');
	InitBoard(Bombs, ROWS, COLS, '0');
	SetBombs(Bombs, ROW, COL, BOMBSNUM);
	ShowBoard(Board, ROW, COL);
	printf("\n");
	flag = FindBombs(Board, Bombs, ROW, COL);
	if (flag == 'F')
	{
		printf("��λ��Ϊը������Ϸ����\n");
	}
	else
	{
		printf("��Ϸʤ��\n");
	}
}

int main()
{
	int n;
	char board[ROWS][COLS] = { 0 };
	char bombs[ROWS][COLS] = { 0 };
	srand((int)time(NULL));
	do
	{
		GameMenu();
		printf("����������ѡ��\n");
		scanf("%d", &n);

		switch (n)
		{
		case 1:
			Game(board, bombs, ROWS, COLS);
			break;
		case 0:
			printf("������Ϸ\n");
			break;
		default:
			printf("�����������������\n");
			break;
		}

	}while (n);

	return 0;
}

