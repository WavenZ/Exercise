#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define maxn 10
int HL[maxn][maxn - 1];//横线/0行列不用
int VL[maxn][maxn - 1];//竖线//0行列不用
int n;//方阵的边长
int nLine;//边的个数
int cntSquares(int length);
int main() {
	int cnt = 1;
	int temp=0,squareCnt=0;
	freopen("data.txt", "r", stdin);
	while (~scanf("%d %d", &n, &nLine)) {
		memset(HL, 0, sizeof(HL));
		memset(VL, 0, sizeof(VL));
		squareCnt = 0;
		for (int k = 0; k < nLine; ++k) {
			char ch, i, j;
			scanf("%s %d %d", &ch, &i, &j);
			if (ch == 'H') HL[i][j] = 1;
			else VL[i][j] = 1;
		}
		if (cnt > 1) printf("\n**********************************\n\n");
		printf("Problem #%d\n\n", cnt);
		for (int i = 1; i < n; ++i) {
			temp = cntSquares(i); squareCnt += temp;
			if (temp)printf("%d square (s) of size %d\n", temp, i);
		}
		if (!squareCnt)printf("No completed squares can be found.\n");
		cnt++;
	}
	fclose(stdin);
	return 0;
}
int cntSquares(int length) {
	int cnt = 0;
	for (int i = 1; i <= n - length; ++i)
		for (int j = 1; j <= n - length; ++j) {
			int k;
			for (k = 0; k < length; ++k) {
				if (!HL[i][j + k] || !HL[i + length][j + k]) break;
				if (!VL[j][i + k] || !VL[j + length][i + k]) break;
			}
			if (k == length) cnt++;
		}
	return cnt;
}
