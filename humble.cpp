/*
ID: gzxabcd1
PROG: humble
LANG: C++
*/
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <vector>

FILE *fout;

int main(int argc, char ** argv)
{
	FILE* fin = fopen("humble.in", "r");
	fout = fopen("humble.out", "w");

	int ks[100];
	int index[100];
	int r[100001];
	int K, N;
	fscanf(fin, "%d %d", &K, &N);
	for (int i=0; i<K; ++i) {
		fscanf(fin, "%d", &ks[i]);
		index[i] = 0;
	}

	r[0] = 1;
	for (int i=1; i<=N; ++i) {
		while (true) {
			int min = 2147483647;
			int t;
			for (int j=0; j<K; ++j) {
				if (r[index[j]] * ks[j] < min) {
					min = r[index[j]] * ks[j];
					t = j;
				}
			}
			index[t] += 1;
			r[i] = min;
			printf("%d %d\n", i, r[i]);
			if (r[i] != r[i-1]) {
				break;
			}
		}
	}
	printf("%d\n", r[N]);
	fprintf(fout, "%d\n", r[N]);
	


	return 0;
}

