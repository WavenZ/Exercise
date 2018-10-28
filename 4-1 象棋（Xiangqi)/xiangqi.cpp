#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
typedef struct{//���ӽṹ��
	char kind;
	int r, c;
}Piece; 
int n;//�췽������
Piece red[8],General, GeneralX;;//�췽��������2-7 /�ڷ���
char board[10 + 1][9 + 1];//���̣�0��/�в���
void readPieces() {//����
	for (int i = 0; i < n; ++i) {
		scanf("%s %d %d", &red[i].kind, &red[i].r, &red[i].c);//������������
		board[red[i].r][red[i].c] = red[i].kind;//�������б��
	}
}
void boardReset() {//��������
	memset(board, 0, sizeof(board));
	for (int i = 0; i < n; ++i) board[red[i].r][red[i].c] = red[i].kind;//�������б��
}
int checkBack() {//�ڽ��ܷ�ɱ��˧/��������
	int i = General.r+1;
	for (; i <= 10; ++i) {
		if (board[i][General.c]) { if (board[i][General.c] == 'G') return 1;}
		else return 0;//�����ĵ�һ�����Ӳ���˧
	}
	return 0;
}
int generalMove(int dr, int dc) {//ģ��ڽ�����
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
int checkMate() {//�ж��ܷ���
	char piece, r, c;
	for (int i = 0; i < n; ++i) {
		piece = red[i].kind; r = red[i].r; c = red[i].c;
		if (c==GeneralX.c&&r==GeneralX.r) continue;//������ڽ��Ե���
		if (piece == 'G') {//
			int j = r;
			while ((j--) && (board[j][c] == 0)) if (judge(j, c))return 1;
		}
		else if (piece == 'R') {//�����Ե��ĵط���Σ�յ�
			int j = r;
			while ((j-- > 0) && (board[j][c] == 0)) if (judge(j, c))return 1;//��
			j = r;
			while ((j++ < 10) && (board[j][c] == 0)) if (judge(j, c))return 1;//��
			j = c;
			while ((j++ < 9) && (board[r][j] == 0)) if (judge(r, j))return 1;//��
			j = c;
			while ((j-- > 0) && (board[r][j] == 0)) if (judge(r, j))return 1;//��
		}
		else if (piece == 'C') {//���ھ���֮�����һ�����ӵ���Σ�յ�
			int j = c, flag = 0;
			while (j--&& flag < 2) {
				if (board[r][j] !=0) flag++;//�м�����һ��Ԫ��֮��flag=1
				if (flag == 1) if (judge(r, j))return 1;//flag=1ʱΪΣ�յ�
			}
			j = c, flag = 0;
			while (j++ < 10 && flag < 2) {
				if (board[r][j] != 0) flag++;//�м�����һ��Ԫ��֮��flag=1
				if (flag == 1) if (judge(r, j))return 1;//flag=1ʱΪΣ�յ�
			}
			j = r, flag = 0;
			while (j--&& flag < 2) {
				if (board[j][c] != 0) flag++;//�м�����һ��Ԫ��֮��flag=1
				if (flag == 1) if (judge(j, c))return 1;//flag=1ʱΪΣ�յ�
			}
			j = r, flag = 0;
			while (j++ < 10 && flag < 2) {
				if (board[j][c] != 0) flag++;//�м�����һ��Ԫ��֮��flag=1
				if (flag == 1) if (judge(j, c))return 1;//flag=1ʱΪΣ�յ�
			}
		}
		else if (piece == 'H') {//���--�ĸ���ŵ�
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
		readPieces();//��ȡ��������
		if (checkBack()) yes = 0;//�ж��ܷ�ɱ
		else {//�ж��Ƿ񱻽���
			if (yes&&generalMove(-1, 0)) {//�ڽ�����������ܻ�Ե��췽�����ӣ�
				if (!checkMate()) yes = 0;
				boardReset();
			}
			if (yes&&generalMove(1, 0)) {//�ڽ�����������ܻ�Ե��췽�����ӣ�
				if (!checkMate()) yes = 0;
				boardReset();
			}
			if (yes&&generalMove(0, -1)) {//�ڽ�����������ܻ�Ե��췽�����ӣ�
				if (!checkMate()) yes = 0;
				boardReset();
			}
			if (yes&&generalMove(0, 1)) {//�ڽ�����������ܻ�Ե��췽�����ӣ�
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
























































//�ٺ�˧���ڽ�ʱ�����ܽ���
//�ںڽ����ԳԺ���
//�ۺڽ����˺���֮����ܵ�Σ��λ�û�仯
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define r 10
#define c 9
int a[r+1][c+1];//����
int b[r + 1][c + 1];
char red[10][3];//��¼����
int r0, c0;//�ڷ�generalλ��
int n;//�췽���Ӹ���

void mark_piece();
void mark_danger();
int checkmate();
int main() {
	freopen("data.txt", "r", stdin);
	while (scanf("%d %d %d", &n, &r0, &c0) == 3 && n) {
		getchar();
		memset(a, 0, sizeof(a));//���
		memset(b, 0, sizeof(b));//���
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
void mark_piece(){//��������ӵĵ�
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
		else if (piece == 'R') {//�����Ե��ĵط���Σ�յ�
			int j = x;
			while ((j-->0) && (a[j][y] == 0)) mark(j, y);//��
			j = x;
			while ((j++<3) && (a[j][y] == 0)) mark(j, y);//��
			j = y;
			while ((j++<6) && (a[x][j] == 0)) mark(x, j);//��
			j = y;
			while ((j-->4) && (a[x][j] == 0)) mark(x, j);//��
		}
		else if (piece == 'C') {//���ھ���֮�����һ�����ӵ���Σ�յ�
			int j = y, flag = 0;
			while (j--&& flag<2) {
				if (a[x][j] == 1) flag ++;//�м�����һ��Ԫ��֮��flag=1
				if(flag==1) mark(x, j);//flag=1ʱΪΣ�յ�
			}
			j = red[i][2], flag = 0;
			while (j++<10&& flag < 2) {
				if (a[x][j] == 1) flag++;//�м�����һ��Ԫ��֮��flag=1
				if (flag == 1) mark(x, j);//flag=1ʱΪΣ�յ�
			}
			j = x, flag = 0;
			while (j--&& flag < 2) {
				if (a[j][y] == 1) flag++;//�м�����һ��Ԫ��֮��flag=1
				if (flag == 1) mark(j, y);//flag=1ʱΪΣ�յ�
			}
			j = x, flag = 0;
			while (j++<10&& flag < 2) {
				if (a[j][y] == 1) flag++;//�м�����һ��Ԫ��֮��flag=1
				if (flag == 1) mark(j, y);//flag=1ʱΪΣ�յ�
			}
		}
		else if (piece == 'H') {//���--�ĸ���ŵ�
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
