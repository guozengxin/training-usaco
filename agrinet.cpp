/*
ID: gzxabcd1
PROG: agrinet
LANG: C++
*/
#include <stdio.h>
#include <math.h>
#include <memory.h>

const int MAXN = 100;
const int INF = 100000000;

FILE *fout;
int N;
int dis[MAXN][MAXN];

void Prim() 
{
	bool stat[MAXN] = {false};
	stat[0] = true;
	int innum = 1;
	int minres = 0;
	while (innum < N) {
		int mindis = INF;
		int v = -1;
		for (int i=0; i<N; ++i) {
			for (int j=0; j<N; ++j) {
				if (i != j && stat[i] && !stat[j] && mindis > dis[i][j]) {
					mindis = dis[i][j];
					v = j;
				}
			}
		}
		stat[v] = true;
		minres += mindis;
		innum += 1;
	}
	fprintf(fout, "%d\n", minres);
}

int main(int argc, char ** argv)
{
	FILE* fin = fopen("agrinet.in", "r");
	fout = fopen("agrinet.out", "w");
	fscanf(fin, "%d", &N);
	for (int i=0; i<N; ++i) {
		for (int j=0; j<N; ++j) {
			fscanf(fin, "%d", &dis[i][j]);
		}
	}
	Prim();

	return 0;
}

