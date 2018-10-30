#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
typedef struct {
	int x, y;
	int dir[8];
}Move;
Move move[64];
int Nmove = 0;
//上、下、左、右、左上、右上、左下、右下
int dx[8] = { -1,1,0,0,-1,-1,1,1 }, dy[8] = { 0,0,-1,1,-1,1,-1,1 };
int nWhite, nBlack;//黑白棋子数
char board[9 + 1][9 + 1];//多1行/列，防止溢出
char cmd[4], player;//指令最长为3个字符
void exec_cmd();//执行命令
void make_a_move();//下棋
int main() {
	
	int n;
	freopen("data.txt", "r", stdin);
	memset(board, 0, sizeof(board));
	scanf("%d", &n);
	while (n--) {
		memset(move, 0, sizeof(move));
		if (cmd[0]) printf("\n");//除了第一局之前都加上\n
		for (int i = 1; i <= 8; ++i) scanf("%s", &board[i][1]);
		do {
			scanf("%s", cmd);//读取命令
			exec_cmd();//执行命令
		} while (cmd[0] != 'Q');
	}
	fclose(stdin);
	return 0;
}
void find_legal_move();//查找合法位置
void list_legal_move();//列出合法位置
void print_board();//打印棋局
void exec_cmd() {
	if (cmd[0] == 'W') player = 1;
	else if (cmd[0] == 'B') player = 0;
	else if (cmd[0] == 'M') make_a_move();
	else if (cmd[0] == 'L') list_legal_move();
	else if (cmd[0] == 'Q') print_board();
}
void find_legal_move() {
	char mine,rival, flag = 0;
	Nmove = 0;//合法点计数
	memset(move, 0, sizeof(move));
	if (player) mine = 'W',rival='B';
	else mine = 'B',rival='W';
	for(int i=1;i<=8;++i)//遍历所有位置
		for (int j = 1; j <= 8; ++j) {
			if (board[i][j] != '-') continue;
			flag = 0;
			for (int k = 0; k < 8; ++k)//八个方向
				if (board[i + dx[k]][j + dy[k]] == rival)
					for (int m = i + dx[k], n = j + dy[k]; m > 0 && n > 0 && m < 9 && n < 9; m += dx[k], n += dy[k]) {
						if (board[m][n] == '-') break;
						if (board[m][n] == mine) {
							move[Nmove].dir[k] = 1; flag = 1;
						}
					}
			if (flag) {move[Nmove].x = i; move[Nmove].y = j; Nmove++;}
		}
}
void list_legal_move() {
	find_legal_move();
	if (Nmove == 0) {
		printf("No legal move.\n");
		return;
	}
	int i = 0;
	for (; i < Nmove-1; ++i) {
		printf("(%d,%d) ", move[i].x, move[i].y);
	}
	printf("(%d,%d)\n", move[i].x, move[i].y);
}
void count();
void make_a_move() {
	char mine,rival;//自己-对手
	int tempx, tempy;
	find_legal_move();
	if (Nmove == 0) {
		player = 1 - player;
		find_legal_move();
	}
	if (player) mine = 'W', rival = 'B';
	else mine = 'B', rival = 'W';
	for (int i = 0; i < Nmove; ++i)
		if (move[i].x == cmd[1]-'0' && move[i].y == cmd[2]-'0') {
			tempx = move[i].x; tempy = move[i].y;
			board[tempx][tempy] = mine;
			for (int k = 0; k < 8; ++k)
				if(move[i].dir[k])
					for(int m=tempx+dx[k],n=tempy+dy[k]; m > 0 && n > 0 && m < 9 && n < 9; m += dx[k], n += dy[k])
						if (board[m][n] == mine) break;
						else board[m][n] = mine;	
		}
	count();
	printf("Black -%3d White -%3d\n", nBlack, nWhite);//坑爹的3d
	player = 1 - player;
}
void print_board(){
	for (int i = 1; i <= 8; ++i) printf("%s\n", &board[i][1]);
}
void count() {
	nWhite=0, nBlack=0;
	for (int i = 1; i <= 8; ++i)
		for (int j = 1; j <= 8; ++j)
			if (board[i][j] == 'W') nWhite++;
			else if(board[i][j] == 'B') nBlack++;
}