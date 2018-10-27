#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int main() {
	int a, b;
	int s[51];
	int r[51];
	int cnt = 0;
	int start, end;
	int n = 1;
	int ch;
	int repeat = 0;
	int zero = 0;
	freopen("data.txt", "r", stdin);
	while(~scanf("%d %d", &a, &b)){
		if(n++>1) printf("\n");
		printf("%d/%d = %d.", a, b, a / b);
		repeat = cnt= start = zero = end =0;
		memset(s, 0, sizeof(s));
		while (cnt<50) {
			for (int i = 0; i < cnt; ++i)//搜寻余数是否出现过 
				if (r[i] == a % b) {
					start = i;
					end = cnt - 1;
					repeat = 1;
					//if(r[i]==0)zero = 1;
				}
			if (repeat) break;
			else {
				r[cnt] = a % b;
				a = (a % b) * 10;
				s[cnt] = a / b;
				cnt++;
			}	
		}
		if (repeat) {
			for (int i = 0; i < start; ++i)printf("%d", s[i]);
			printf("(");
			for (int i = start; i <= end; ++i)printf("%d", s[i]);
			printf(")\n");
			printf("   %d = number of digits in repeating cycle\n", zero?0:end - start + 1);
		}
		else {
			printf("(");
			for (int i = 0; i < 50; ++i)printf("%d", s[i]);
			printf("...)\n");
			printf("   99 = number of digits in repeating cycle\n");
		}

	} 
	fclose(stdin);
	return 0;
}