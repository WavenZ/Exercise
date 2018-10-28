#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
char temp[12];
char a[6], b[6];//保存输入
int R[3][3];//旋转矩阵
int Sin(int a);
int Cos(int a);
void updateR(int pitch, int roll, int yaw);
void Rotate(char c[6]);
int main() {
	int flag = 0;
	freopen("data.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	while (scanf("%s", temp) != EOF) {
		memcpy(b, temp + 6, 6 * sizeof(char));
		flag = 0;
		for (int i = 0; i < 360; i += 90)
			for (int j = 0; j < 360; j += 90)
				for (int k = 0; k < 360; k += 90) {
					memcpy(a, temp, 6 * sizeof(char));
					updateR(i, j, k);
					Rotate(a);
					printf("%s\n", a);
					if (strcmp(a, b) == 0) {
						flag = 1;
						//i = j = k = 360;
					}
				}
		//if (flag) printf("TRUE\n");
		//else printf("FALSE\n");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
void Multi(int r[3][3], int m[3][6], int a[3][6]) {
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 6; ++j) {
			a[i][j] = r[i][0] * m[0][j] + r[i][1] * m[1][j] + r[i][2] * m[2][j];
		}
}
void Rotate(char c[6]) {
	int Mat[3][6] = { 0 }, Ret[3][6] = { 0 };
	//矢量转矩阵
	Mat[2][0] = c[0]; Mat[0][1] = c[1]; Mat[1][2] = -c[2];
	Mat[1][3] = c[3]; Mat[0][4] = -c[4]; Mat[2][5] = -c[5];
	//旋转矩阵作用于矩阵
	Multi(R, Mat, Ret);
	for (int i = 0; i < 6; ++i) {
		if (Ret[2][i] > 0) c[0] = Ret[2][i];
		else if (Ret[0][i] > 0) c[1] = Ret[0][i];
		else if (Ret[1][i] < 0) c[2] = -Ret[1][i];
		else if (Ret[1][i] > 0) c[3] = Ret[1][i];
		else if (Ret[0][i] < 0) c[4] = -Ret[0][i];
		else if (Ret[2][i] < 0) c[5] = -Ret[2][i];
	}
}
void updateR(int pitch, int roll, int yaw) {//更新旋转矩阵
	//3-1-2旋转矩阵（Z-X-Y）
	R[0][0] = Cos(pitch)*Cos(yaw) - Sin(roll)*Sin(pitch)*Sin(yaw);
	R[0][1] = Cos(pitch)*Sin(yaw) + Sin(roll)*Sin(pitch)*Cos(yaw);
	R[0][2] = -Cos(roll)*Sin(pitch);
	R[1][0] = -Cos(roll)*Sin(yaw);
	R[1][1] = Cos(roll)*Cos(yaw);
	R[1][2] = Sin(roll);
	R[2][0] = Sin(pitch)*Cos(yaw) + Sin(roll)*Cos(pitch)*Sin(yaw);
	R[2][1] = Sin(pitch)*Sin(yaw) - Sin(roll)*Cos(pitch)*Cos(yaw);
	R[2][2] = Cos(roll)*Cos(pitch);
}
//为了简化三角运算，自定义三角函数如下
int Sin(int a) {//a的取值应为0、90、180、270
	if (a == 90) return 1;
	else if (a == 270) return -1;
	else return 0;
}
int Cos(int a) {//a的取值应为0、90、180、270
	if (a == 0 || a == 360) return 1;
	else if (a == 90 || a == 270) return 0;
	else return -1;
}


