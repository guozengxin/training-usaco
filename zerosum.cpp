/*
ID: gzxabcd1
PROG: zerosum
LANG: C++
*/
#include <stdio.h>
#include <string>
#include <vector>

int N;
FILE* fin = fopen("zerosum.in", "r");
FILE* fout = fopen("zerosum.out", "w");

int calsum(char* signlist)
{
	int sum = 0;
	signlist[0] = '+';
	int i, time, lastnum;
	for (i = N, time = 1, lastnum = 0; i >= 1; i --) {
		lastnum += i * time;
		switch (signlist[i-1]) {
			case '+':
				sum += lastnum;
				time = 1;
				lastnum = 0;
				break;
			case '-':
				sum -= lastnum;
				time = 1;
				lastnum = 0;
				break;
			case ' ':
				time *= 10;
				break;
		}
	}
	return sum;
}

void sumtry(int num, char* signlist)
{
	if (num == N) {
		if (calsum(signlist) == 0) {
			for (int i = 1; i < N; ++ i) {
				fprintf(fout, "%d%c", i, signlist[i]);
			}
			fprintf(fout, "%d\n", N);
		}
		return;
	}

	signlist[num] = ' ';
	sumtry(num + 1, signlist);
	signlist[num] = '+';
	sumtry(num + 1, signlist);
	signlist[num] = '-';
	sumtry(num + 1, signlist);
}

int zero_list()
{
	char* signlist = new char[N];
	for (int i = 0; i < N; i ++) {
		signlist[i] = 'n';
	}
	sumtry(1, signlist);
	delete[] signlist;
}

int main(int argc, char** argv)
{
	fscanf(fin, "%d", &N);
	zero_list();
	//char signlist[10] = "n -+-";
	//printf("%d\n", calsum(signlist));
	fclose(fin);
	fclose(fout);
}
