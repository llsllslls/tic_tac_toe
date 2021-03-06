// study.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//negamax alphabeta
//基本要求：实现4*4,6*6,8*8的tic-tac-toe（3*3连线），给出pv，搜索节点个数等信息
//X为人类，先走。

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
#define N 3
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';

 

struct node
{
	vector<char> board;
	int value;
};

void printboard(const vector<char>& board)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j != N-1)
			{
              cout << board[i*N+j] << " | ";
			}
			else  cout << board[i*N + j];
			
		}
		cout << endl;
		if (i != N-1)
		{
        cout << "----------------------------" << endl;
		}
		
	}
}
bool isLegal(int number, const vector<char>& board)
{
	return (board[number] == EMPTY && number<N*N && number>=0);
}

void move( vector<char>& board)
{
	int number;
	cout << "走棋" << endl;
	cin >> number;
	if (isLegal(number, board))
	{
		board[number] = X;
	}
	else
	{
	cout << "重新选择" << endl;
	move(board);
	}

}

char winner(const vector<char>& board,char M)		
{
	int m = 1;
  for(int i=0;i<N;i++)
  {
	  if (m)
	  {
		  for (int j = 0; j < N; j++)
		  {
			  if (j + 2 < N)
			  {
				  if (board[i*N + j] == M && board[i*N + j + 1] ==M && board[i*N + j + 2] == M)
				  {
					  m = 0;
					  return M;
					  break;
				  }
				  if (i + 2 < N)
				  {
					  if(board[i*N + j] == M && board[(i + 1)*N + (j + 1)] ==M && board[(i + 2)*N + (j + 2)] == M )
				  	  {
					    m = 0;
					    return M;
					    break;
				      }
				  }
			  }
			  if (i + 2 < N)
			  {
				  if (board[i*N + j] == M && board[(i + 1)*N + j] == M && board[(i + 2)*N + j] == M)
				  {
					  m = 0;
					  return M;
					  break;
				  }
				  if (j - 2 > 0)
				  {
					  if (board[i*N + j] == M && board[(i + 1)*N + (j - 1)] ==M &&  board[(i + 2)*N + (j - 2)] == M )
					  {
						  m = 0;
						  return M;
						  break;
					  }
				  }

			  }
		  }
	  }
  }
  if (m) return 0;
}
int noempty(vector<char>& board) //0:不满 1：满
{
	if (count(board.begin(), board.end(), EMPTY) == 0)
		return 1;
	else return 0;
}
int gameisover(vector<char>& board)
{
	if (noempty(board) || winner(board,X)|| winner(board, O)) return 1;
	else return 0;
}
int gettypeboard(vector<char>& board,char M)
{
	int n = 0;
	for ( int i = 0;  i < N;  i++)
	{
		for (int j = 0; j < N; j++)
		{
			int m = i * N + j;
			if (j + 2 < N)
			{
				if (board[m] == M && board[m + 1] == M && board[m + 2] == EMPTY) //横正向 MM空
					n = n + 2;
				if (i + 2 < N)
				{
					if (board[i * N + j] == M && board[(i + 1) * N + j + 1] == M && board[(i + 2) * N + j + 2] == EMPTY )   //正对角线向下 MM空
						n = n + 2;
					if (i - 1 > 0 && j - 1 > 0)
					{
						if (board[i * N + j] ==M && board[(i + 1) * N + j + 1] == M && board[(i + 2) * N + j + 2] == EMPTY && board[(i - 1) * N + j - 1] == EMPTY)  //正对角线 空MM空
							n = n + 20;
					}
				}
				if (i - 2 > 0)
				{
					if (board[i * N + j] == M && board[(i - 1) * N + j + 1] == M && board[(i - 2) * N + j + 2] == EMPTY ) //反对角线向下 MM空
						n = n + 2;
				}
			}
			if (j - 2 > 0)
			{
				if (board[m] == M && board[m - 1] == M && board[m - 2] == EMPTY) //横反向  空MM
					n = n + 2;
				if (j + 1 < N)
				{
					if (board[m] == M && board[m - 1] == M && board[m - 2] == EMPTY && board[m + 1] == EMPTY) //横向 空MM空
						n = n + 20;
				}
				if (i - 2 > 0)
				{
					if (board[i * N + j] == M && board[(i - 1) * N + j - 1] == M && board[(i - 2) * N + j - 2] == EMPTY) //正对角线向上 空MM 
						n = n + 2;
 				}
			}
			if (i + 2 < N)
			{
				if (board[i * N + j] == M && board[(i + 1) * N + j] == M && board[(i + 2) * N + j] == EMPTY)   //竖向下 MM空
					n = n + 2;
				if (j - 2 > 0)
				{
					if (board[i * N + j] == M && board[(i + 1) * N + j - 1] == M && board[(i + 2) * N + j - 2] == EMPTY ) //反对角线向上 空MM
					n = n + 2;
				}
			}
			if (i - 2 > 0)
			{
				if (board[i * N + j] == M && board[(i - 1) * N + j] == M && board[(i - 2) * N + j] == EMPTY )  //竖向上 空MM
					n = n + 2;

			}
			if (i - 2 > 0 && i + 1 < N)
			{
				if (board[i * N + j] == M && board[(i - 1) * N + j] == M && board[(i - 2) * N + j] == EMPTY && board[(i + 1) * N + j] == EMPTY )  //竖 M空空M 
					n = n + 20;
				if (j + 2 < N  && j - 1 > 0)
				{
					if (board[i * N + j] == M && board[(i - 1) * N + j + 1] == M && board[(i - 2) * N + j + 2] == EMPTY && board[(i + 1) * N + j - 1] == EMPTY )  //反对角线 空MM空
						n = n + 20;
				}

			}
			if (j + 1 < N && j - 1 > 0 && i - 1 > 0 && i + 1 < N)
			{
				if (board[m] == M && board[m + 1] == EMPTY && board[m - 1] == EMPTY && board[(i + 1) * N + j] == EMPTY && board[(i - 1) * N + j] == EMPTY)  //上下左右为空
					n = n + 2;
				if (board[m] == M && board[(i + 1) * N + j + 1] == EMPTY && board[(i - 1) * N + j - 1] == EMPTY && board[(i + 1) * N + j - 1] == EMPTY && board[(i - 1) * N + j + 1] == EMPTY)  //斜向为空
					n = n + 2;
		    }
		}
	}
	return n;
}
int cur_value(vector<char>& board)
{
	int curvalue = 0;
	if (gameisover(board))
	{
		if (noempty(board)) curvalue = 0;
		if (winner(board,X) == X) curvalue = 20;
		if (winner(board,O) == O) curvalue = -20;
	}
	else
	{
		curvalue = curvalue + gettypeboard(board,O);
		curvalue = curvalue - gettypeboard(board,X);
	}
	return curvalue;
}

vector<node> generateMoves(struct node node)
{
	char M;
	struct node childnode;
	vector<struct node> childnodes;
	childnode = node;
	if (count(node.board.begin(), node.board.end(), X) > count(node.board.begin(), node.board.end(), O))
	{
		M = O;
	}
	else M = X;
	for (int i = 0; i < N*N; i++)
	{
		if (node.board[i] = EMPTY)
		{
			childnode.board[i] = M;
			childnode.value = cur_value(childnode.board);
			childnodes.push_back(childnode);
		}
	}
	return childnodes;
}
int negamax(struct node node, int depth, int color, int alpha,int beta)
{
	int value = INT_MIN;
	if (depth == 0 || gameisover(node.board))
	{
		value = cur_value(node.board);
		return color*value;
	}
	else
	{
	  struct node childnode;	  
	  for (auto u : generateMoves(node))
	  {
		  cout <<endl<< "childnode:" << endl;
		  printboard(u.board);
		value = max(value, -negamax(u, depth - 1, -color, -alpha, -beta));
		alpha = max(alpha, value);
	    if (alpha > beta)  break;
	  }
	  return value;
	}

}

int main()
{
	vector<char> board(N*N, EMPTY);
	printboard(board);
	while (!gameisover(board))
	{
	  struct node childnodes;
	  move(board);
	  printboard(board);
	  struct node rootnode;
	  rootnode.board = board;
	  int value = negamax(rootnode,2,1,INT_MIN,INT_MAX);
	  if (childnodes.value = value)
	  {
		  board = childnodes.board;
	  }
	  printboard(board);
	}
	if (noempty(board))
	{
		cout << "平局" << endl;
	}
	else if (winner(board, X) == X)
	{
		cout << "the winner is you" << endl;
	}
	else 		
		cout << "the winner is computer" << endl;
	return 0;
}