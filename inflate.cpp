/*
ID: gzxabcd1
PROG: inflate
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <algorithm>

struct Item {
	int point;
	int time;
	Item(int p, int t):point(p), time(t)
	{
	}
};

FILE *fout;
int M, N;                                        
std::vector<Item> alltypes; 
int result[10001] = {0};

int max(int a, int b)
{
	return a > b ? a : b;
}

int Solve()
{
	for (int w=0; w<=M; ++w) {
		if (w==0) {
			result[w] = 0;
		} else {
			int maxt = 0;
			for (int k=0; k<N; ++k) {
				int t = alltypes[k].time;
				if (w-t >= 0 && maxt < (alltypes[k].point + result[w-t])) {
					maxt = alltypes[k].point + result[w-t];
				}
			}
			result[w] = max(result[w-1], maxt);
		}
	}
	fprintf(stderr, "%d\n", result[M]);
	return result[M];
}

int main(int argc, char ** argv)
{
	FILE* fin = fopen("inflate.in", "r");
	fout = fopen("inflate.out", "w");
	fscanf(fin, "%d %d", &M, &N);
	for (int i=0; i<N; ++i) {
		int p, t;
		fscanf(fin, "%d %d", &p, &t);
		Item it(p, t);
		alltypes.push_back(it);
	}
	int r = Solve();
	fprintf(fout, "%d\n", r);

	return 0;
}

