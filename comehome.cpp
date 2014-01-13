/*
ID: gzxabcd1
PROG: comehome
LANG: C++
*/
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <vector>

const int INF = 100000000;

int P;
typedef struct ArcNode_ {
	char name;
	int distance;
} ArcNode;

typedef struct VNode_ {
	char name;
	std::vector<ArcNode> arcs;
}VNode;

std::vector<VNode> allnodes;
FILE *fout;
int minres = INF;
char cres = 0;

void addArc(char c1, char c2, int d)
{
	if (c2 == 'Z' && c1 >= 'A' && c1 < 'Z' && minres > d) {
		cres = c1;
		minres = d;
	}
	int k;
	for (k=0; k<allnodes.size(); ++k) {
		if (c1 == allnodes[k].name) {
			std::vector<ArcNode> &arcs = allnodes[k].arcs;
			int i;
			for (i=0; i<arcs.size(); i++) {
				if (arcs[i].name == c2) {
					if (arcs[i].distance < d) {
						arcs[i].distance = d;
					}
					break;
				}
			}
			if (i == arcs.size()) {
				ArcNode an;
				an.name = c2;
				an.distance = d;
				arcs.push_back(an);
			}
			break;
		}
	}
	if (k == allnodes.size()) {
		VNode vn;
		vn.name = c1;
		ArcNode an;
		an.name = c1;
		an.distance = 0;
		vn.arcs.push_back(an);
		an.name = c2;
		an.distance = d;
		vn.arcs.push_back(an);
		allnodes.push_back(vn);
	}
}

void Dijkstra(char startidx)
{
	std::vector<int> dis(allnodes.size(), INF);
	std::vector<int> stat(allnodes.size(), 0);
	dis[startidx] = 0;
	int leftnum = allnodes.size() - 1;
	while (leftnum > 0) {
		int mindis = INF;
		int v = -1;
		for (int j=0; j<dis.size(); ++j) {
			if (stat[j]==0 && mindis > dis[j]) {
				v = j;
				mindis = dis[j];
			}
		}
		if (v == -1) break;
		stat[v] = 1;
		leftnum -= 1;
		for (int j=0; j<allnodes[v].arcs.size(); ++j) {
			char c = allnodes[v].arcs[j].name;
			int d = allnodes[v].arcs[j].distance;
			int k = 0;
			for (k=0; k<allnodes.size(); ++k) {
				if (allnodes[k].name == c) {
					break;
				}
			}
			if (dis[k] > dis[v] + d) {
				dis[k] = dis[v] + d;
			}
			if (c >= 'A' && c < 'Z' && minres > dis[k]) {
				minres = dis[k];
				cres = c;
			}
		}
	}
}

int main(int argc, char ** argv)
{
	FILE* fin = fopen("comehome.in", "r");
	fout = fopen("comehome.out", "w");
	fscanf(fin, "%d\n", &P);
	char c1;
	char c2;
	int d;
	for (int i=0; i<P; ++i) {
		fscanf(fin, "%c %c %d\n", &c1, &c2, &d);
		addArc(c1, c2, d);
		addArc(c2, c1, d);
	}
	for (int i=0; i<allnodes.size(); ++i) {
		if (allnodes[i].name == 'Z') {
			Dijkstra(i);
		}
	}
	printf("%c %d\n", cres, minres);
	fprintf(fout, "%c %d\n", cres, minres);

	return 0;
}

