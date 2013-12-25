/*
ID: gzxabcd1
PROG: money
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <memory.h>

FILE* fout;

long long cal_money(const int N, const std::vector<int>& vlist)
{
	long long dp[10001];
	memset(dp, 0, sizeof(dp));
	dp [0] = 1;
	for (size_t i = 0; i < vlist.size(); ++ i) {
		int j;
		for (j = vlist[i]; j <= N; j ++) {
			dp[j] += dp[j-vlist[i]];
		}
	}
	return dp[N];
}

int main(int argc, char** argv)
{
	int V, N;
	std::vector<int> vlist;
	FILE* fin = fopen("money.in", "r");
	fout = fopen("money.out", "w");
	fscanf(fin, "%d %d", &V, &N);
	int v;
	std::vector<int>::iterator itr;
	for (int i = 0; i < V; i ++) {
		fscanf(fin, "%d", &v);
		vlist.push_back(v);
	}
	long long ret = cal_money(N, vlist);

	fprintf(fout, "%lld\n", ret);
	fclose(fin);
	fclose(fout);
	return 0;
}
