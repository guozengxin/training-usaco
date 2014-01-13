/*
ID: gzxabcd1
PROG: cowtour
LANG: C++
*/
#include <stdio.h>
#include <math.h>
#include <memory.h>

const double INF = 1e15;
const int MAXN = 152;

struct Point {
	int x;
	int y;
};

Point points[MAXN];
double dis[MAXN][MAXN];
int N;

double distance(Point *p1, Point *p2)
{
	double dis = 0;
	dis = sqrt((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y));
	return dis;
}

void Floyd_Warshall()
{
	for (int k=0; k<N; ++k) {
		for (int i=0; i<N; ++i) {
			for (int j=0; j<N; ++j) {
				if (dis[i][k] + dis[k][j] < dis[i][j]) {
					dis[i][j] = dis[i][k] + dis[k][j];
				}
			}
		}
	}
}

double Solve()
{
	double maxd[MAXN];
	int i;
	int j;
	memset(maxd, 0, MAXN);
	double res = INF;
	for (i=0; i<N; ++i) {
		for (j=0; j<N; ++j) {
			if (dis[i][j] != INF && maxd[i] < dis[i][j]) {
				maxd[i] = dis[i][j];
			}
		}
	}
	for (i=0; i<N; ++i) {
		for (j=0; j<N; ++j) {
			if (dis[i][j] == INF) {
				if (distance(&points[i], &points[j]) + maxd[i] + maxd[j] < res) {
					res = distance(&points[i], &points[j]) + maxd[i] + maxd[j];
				}
			}
		}
	}

	for (i=0; i<N; ++i) {
		if (maxd[i] > res) {
			res = maxd[i];
		}
	}

	return res;
}

void printdis()
{
	for (int i=0; i<N; ++i) {
		for (int j=0; j<N; ++j) {
			if (dis[i][j] != INF) {
				printf("%d %d %f\n", i, j, dis[i][j]);
			}
		}
	}
	printf("\n");
}

int main(int argc, char ** argv)
{
	FILE* fin = fopen("cowtour.in", "r");
	FILE* fout = fopen("cowtour.out", "w");
	fscanf(fin, "%d", &N);
	for (int i=0; i<N; ++i) {
		fscanf(fin, "%d %d", &points[i].x, &points[i].y);
	}
	char c;
	for (int i=0; i<N; ++i) {
		fscanf(fin, "%c", &c);
		for (int j=0; j<N; ++j) {
			fscanf(fin, "%c", &c);
			if (i == j) {
				dis[i][j] = 0;
			} else if (c == '0') {
				dis[i][j] = INF;
			} else if (c == '1') {
				dis[i][j] = distance(&points[i], &points[j]);
			}
		}
	}
	Floyd_Warshall();
	double res = Solve();
	fprintf(stderr, "%.6f\n", res);
	fprintf(fout, "%.6f\n", res);

	return 0;
}

