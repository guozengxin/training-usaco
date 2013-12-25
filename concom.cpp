/*
ID: gzxabcd1
PROG: concom
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <memory.h>

const int MaxCount = 101;
FILE * fout;

int main(int argc, char ** argv)
{
	FILE* fin = fopen("concom.in", "r");
	fout = fopen("concom.out", "w");
	int N;
	fscanf(fin, "%d", &N);
	int initData[MaxCount][MaxCount];
	memset(initData, 0, sizeof(initData));
	int max_num = 0;
	for (int kk = 0; kk < N; kk ++) {
		int i, j, p;
		fscanf(fin, "%d %d %d", &i, &j, &p);
		initData[i][j] = p;
		if (max_num < i) 
			max_num = i;
		if (max_num < j)
			max_num = j;
	}

	bool change = true;
	bool own[MaxCount][MaxCount];
	int conState[MaxCount][MaxCount];
	memset(own, false, sizeof(own));
	memset(conState, 0, sizeof(conState));
	for (int i = 1; i <= max_num; i ++) {
		own[i][i] = true;
	}
	while (change) {
		change = false;
		memset(conState, 0, sizeof(conState));
		for (int i = 1; i <= max_num; i ++) {
			for (int j = 1; j <= max_num; j ++) {
				if (own[i][j]) {
					for (int j2 = 1; j2 <= max_num; j2 ++) {
						conState[i][j2] += initData[j][j2];
					}
				}
			}
		}

		for (int i = 1; i <= max_num; i ++) {
			for (int j = 1; j <= max_num; j ++) {
				if (conState[i][j] > 50 && own[i][j] == false) {
					own[i][j] = true;
					change = true;
				}
			}
		}
	}

	for (int i = 1; i <= max_num; i ++) {
		for (int j = 1; j <= max_num; j ++) {
			if (own[i][j] && i != j) {
				fprintf(fout, "%d %d\n", i, j);
			}
		}
	}
	
}
