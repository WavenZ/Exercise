#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void swap(int *a, int *b);
void mysort(int a[6][2]);
int main() {
	int a[6][2];
	char ch;
	int possible = 0;
	freopen("data.txt", "r", stdin);
	do {
		possible = 0;
		for (int i = 0; i < 6; ++i) {
			scanf("%d %d", &a[i][0], &a[i][1]);
		}
		mysort(a);
		if (a[0][0] == a[1][0] && a[0][0] == a[2][0] && a[0][0] == a[3][0])
			if (a[2][1] == a[3][1] && a[2][1] == a[4][1] && a[2][1] == a[5][1])
				if (a[0][1] == a[1][1] && a[0][1] == a[4][0] && a[0][1] == a[5][0])
					possible = 1;
		if (possible)
			printf("POSSIBLE\n");
		else printf("IMPOSSIBLE\n");
	} while ((ch = getchar()) != EOF);

	fclose(stdin);
	return 0;
}
void swap(int *a, int *b) {
	int temp;
	temp = *a;*a = *b;*b = temp;
}
void mysort(int a[6][2]) {
	for (int i = 0; i < 6; ++i) 
		if (a[i][0] < a[i][1])swap(&a[i][0], &a[i][1]);
	for (int i = 0; i < 6; ++i)
		for (int j = 5; j >i ; --j)
			if (a[j][0] > a[j - 1][0]) {
				swap(&a[j][0], &a[j - 1][0]);swap(&a[j][1], &a[j - 1][1]);
			}
			else if ((a[j][0] == a[j - 1][0]) && (a[j][1] > a[j - 1][1])) {
				swap(&a[j][0], &a[j - 1][0]);swap(&a[j][1], &a[j - 1][1]);
			}
}