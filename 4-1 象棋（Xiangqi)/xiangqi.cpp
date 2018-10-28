#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
typedef struct{//棋子结构体
	char kind;
	int r, c;
}Piece; 
int n;//红方棋子数
Piece red[8],General, GeneralX;;//红方棋子数，2-7 /黑方将
char board[10 + 1][9 + 1];//棋盘，0行/列不用
void readPieces() {//输入
	for (int i = 0; i < n; ++i) {
		scanf("%s %d %d", &red[i].kind, &red[i].r, &red[i].c);//读入棋子数据
		board[red[i].r][red[i].c] = red[i].kind;//在棋盘中标记
	}
}
void boardReset() {//重置棋盘
	memset(board, 0, sizeof(board));
	for (int i = 0; i < n; ++i) board[red[i].r][red[i].c] = red[i].kind;//在棋盘中标记
}
int checkBack() {//黑将能否反杀红帅/沿列搜索
	int i = General.r+1;
	for (; i <= 10; ++i) {
		if (board[i][General.c]) { if (board[i][General.c] == 'G') return 1;}
		else return 0;//遇到的第一个棋子不是帅
	}
	return 0;
}
int generalMove(int dr, int dc) {//模拟黑将走棋
	if((General.c+dc)>=4&& (General.c + dc) <= 7)
		if ((General.r + dr) >= 1 && (General.r + dr) <= 3) {
			GeneralX.r = General.r + dr;GeneralX.c = General.c + dc;
			board[GeneralX.r][GeneralX.c] = 0;
			return 1;
		}
	return 0;
}
int judge(char r, char c) {
	if (r == GeneralX.r&&c == GeneralX.c)return 1;
	else return 0;
}
int checkMate() {//判断能否将死
	char piece, r, c;
	for (int i = 0; i < n; ++i) {
		piece = red[i].kind; r = red[i].r; c = red[i].c;
		if (c==GeneralX.c&&r==GeneralX.r) continue;//如果被黑将吃掉了
		if (piece == 'G') {//
			int j = r;
			while ((j--) && (board[j][c] == 0)) if (judge(j, c))return 1;
		}
		else if (piece == 'R') {//车可以到的地方是危险点
			int j = r;
			while ((j-- > 0) && (board[j][c] == 0)) if (judge(j, c))return 1;//上
			j = r;
			while ((j++ < 10) && (board[j][c] == 0)) if (judge(j, c))return 1;//下
			j = c;
			while ((j++ < 9) && (board[r][j] == 0)) if (judge(r, j))return 1;//右
			j = c;
			while ((j-- > 0) && (board[r][j] == 0)) if (judge(r, j))return 1;//左
		}
		else if (piece == 'C') {//和炮距离之间相隔一个棋子的是危险点
			int j = c, flag = 0;
			while (j--&& flag < 2) {
				if (board[r][j] !=0) flag++;//中间遇到一个元素之后flag=1
				if (flag == 1) if (judge(r, j))return 1;//flag=1时为危险点
			}
			j = c, flag = 0;
			while (j++ < 10 && flag < 2) {
				if (board[r][j] != 0) flag++;//中间遇到一个元素之后flag=1
				if (flag == 1) if (judge(r, j))return 1;//flag=1时为危险点
			}
			j = r, flag = 0;
			while (j--&& flag < 2) {
				if (board[j][c] != 0) flag++;//中间遇到一个元素之后flag=1
				if (flag == 1) if (judge(j, c))return 1;//flag=1时为危险点
			}
			j = r, flag = 0;
			while (j++ < 10 && flag < 2) {
				if (board[j][c] != 0) flag++;//中间遇到一个元素之后flag=1
				if (flag == 1) if (judge(j, c))return 1;//flag=1时为危险点
			}
		}
		else if (piece == 'H') {//马儿--四个别脚点
			if (!board[r][c + 1]) { if (judge(r-1, c+2))return 1; if (judge(r+1, c+2))return 1; }
			if (!board[r - 1][c]) { if (judge(r-2, c+1))return 1; if (judge(r-2, c-1))return 1; }
			if (!board[r][c - 1]) { if (judge(r-1, c-2))return 1; if (judge(r+1, c-2))return 1; }
			if (!board[r + 1][c]) { if (judge(r+2, c-1))return 1; if (judge(r+2, c+1))return 1; }
		}
	}
	return 0;
}
int main() {
	int yes = 1;
	freopen("data.txt", "r", stdin);
	while (scanf("%d %d %d", &n, &General.r, &General.c) == 3 && n) {
		yes = 1; memset(board, 0, sizeof(board));
		readPieces();//读取棋子数据
		if (checkBack()) yes = 0;//判断能否反杀
		else {//判断是否被将死
			if (yes&&generalMove(-1, 0)) {//黑将走棋↑（可能会吃掉红方的棋子）
				if (!checkMate()) yes = 0;
				boardReset();
			}
			if (yes&&generalMove(1, 0)) {//黑将走棋↓（可能会吃掉红方的棋子）
				if (!checkMate()) yes = 0;
				boardReset();
			}
			if (yes&&generalMove(0, -1)) {//黑将走棋←（可能会吃掉红方的棋子）
				if (!checkMate()) yes = 0;
				boardReset();
			}
			if (yes&&generalMove(0, 1)) {//黑将走棋→（可能会吃掉红方的棋子）
				if (!checkMate()) yes = 0;
				boardReset();
			}
		}
		if (yes) printf("YES\n");
		else printf("NO\n");
	}
	fclose(stdin);
	return 0;
}
























































//①红帅将黑将时，不能将死
//②黑将可以吃红子
//③黑将吃了红子之后可能的危险位置会变化
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define r 10
#define c 9
int a[r+1][c+1];//棋盘
int b[r + 1][c + 1];
char red[10][3];//记录棋子
int r0, c0;//黑方general位置
int n;//红方棋子个数

void mark_piece();
void mark_danger();
int checkmate();
int main() {
	freopen("data.txt", "r", stdin);
	while (scanf("%d %d %d", &n, &r0, &c0) == 3 && n) {
		getchar();
		memset(a, 0, sizeof(a));//清空
		memset(b, 0, sizeof(b));//清空
		memset(red, 0, sizeof(red));
		for (int i = 0; i < n; ++i) {
			scanf("%c %d %d", &red[i][0], &red[i][1], &red[i][2]);
			getchar();
		}
		getchar();
		mark_piece();
		mark_danger();
		if (checkmate()) printf("YES\n");
		else printf("NO\n");
		for (int i = 1; i <= r; ++i) {
			for (int j = 1; j <= c; ++j)
				if (a[i][j])		printf("* ");
				else if(b[i][j])	printf("X ");
				else				printf("%d ", b[i][j]);
			printf("\n");
		}
		printf("\n");
	}
	fclose(stdin);
	return 0;
}
void mark_piece(){//标记有棋子的点
	for (int i = 0; i < n; ++i) a[red[i][1]][red[i][2]] = 1;
	//a[r0][c0] = 1;
}
void mark(char x, char y) {
	if (x > 0 && x < 4 && y>3 && y < 7)
		b[x][y] = 1;
}
void mark_danger() {
	char piece, x, y;
	for (int i = 0; i < n; ++i) {
		piece = red[i][0]; x = red[i][1]; y = red[i][2];
		if (piece == 'G') {//
			int j = x;
			while ((j--)&&(a[j][y] == 0))mark(j, y);
		}
		else if (piece == 'R') {//车可以到的地方是危险点
			int j = x;
			while ((j-->0) && (a[j][y] == 0)) mark(j, y);//上
			j = x;
			while ((j++<3) && (a[j][y] == 0)) mark(j, y);//下
			j = y;
			while ((j++<6) && (a[x][j] == 0)) mark(x, j);//右
			j = y;
			while ((j-->4) && (a[x][j] == 0)) mark(x, j);//左
		}
		else if (piece == 'C') {//和炮距离之间相隔一个棋子的是危险点
			int j = y, flag = 0;
			while (j--&& flag<2) {
				if (a[x][j] == 1) flag ++;//中间遇到一个元素之后flag=1
				if(flag==1) mark(x, j);//flag=1时为危险点
			}
			j = red[i][2], flag = 0;
			while (j++<10&& flag < 2) {
				if (a[x][j] == 1) flag++;//中间遇到一个元素之后flag=1
				if (flag == 1) mark(x, j);//flag=1时为危险点
			}
			j = x, flag = 0;
			while (j--&& flag < 2) {
				if (a[j][y] == 1) flag++;//中间遇到一个元素之后flag=1
				if (flag == 1) mark(j, y);//flag=1时为危险点
			}
			j = x, flag = 0;
			while (j++<10&& flag < 2) {
				if (a[j][y] == 1) flag++;//中间遇到一个元素之后flag=1
				if (flag == 1) mark(j, y);//flag=1时为危险点
			}
		}
		else if (piece == 'H') {//马儿--四个别脚点
			if (!a[x][y + 1]) {mark(x - 1, y + 2);mark(x + 1, y + 2);}
			if (!a[x - 1][y]) {mark(x - 2, y + 1);mark(x - 2, y - 1);}
			if (!a[x][y - 1]) {mark(x - 1, y - 2);mark(x + 1, y - 2);}
			if (!a[x + 1][y]) {mark(x + 2, y - 1);mark(x + 2, y + 1);}
		}
	}
}
int checkmate(){
	if (r0 == 1 && c0 == 4) { if (!b[r0 + 1][c0] || !b[r0][c0 + 1]) return 0; }
	else if (r0 == 1 && c0 == 5) { if (!b[r0 + 1][c0] || !b[r0][c0 + 1] || !b[r0][c0 - 1]) return 0; }
	else if (r0 == 1 && c0 == 6) {if (!b[r0 + 1][c0] || !b[r0][r0 - 1]) return 0;}
	else if (r0 == 2 && c0 == 4) { if (!b[r0 + 1][c0] || !b[r0 - 1][c0] || !b[r0][c0 + 1]) return 0; }
	else if (r0 == 2 && c0 == 5) { if (!b[r0 - 1][c0] || !b[r0 + 1][c0] || !b[r0][c0 - 1] || !b[r0][c0 + 1]) return 1; }
	else if (r0 == 2 && c0 == 6) { if (!b[r0 - 1][c0] || !b[r0 + 1][c0] || !b[r0][c0 - 1]) return 1; }
	else if (r0 == 3 && c0 == 4) { if (!b[r0 - 1][c0] || !b[r0][c0 + 1]) return 0; }
	else if (r0 == 3 && c0 == 5) { if (!b[r0 - 1][c0] || !b[r0][c0 + 1] || !b[r0][c0 - 1]) return 0; }
	else if (r0 == 3 && c0 == 6) { if (!b[r0 - 1][c0] || !b[r0][c0 - 1]) return 0; }
	return 1;
}
*/
