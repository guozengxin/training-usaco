/*
ID: gzxabcd1
PROG: rect1
LANG: C++
*/
#include <stdio.h>
#include <memory.h>

int x1[1001], y1[1001], x2[1001], y2[1001];
int color[1001];
int area[2501];
int N;
FILE *fout;

void cover(int llx, int lly, int urx, int ury, int floor, int c)
{
	while (floor <= N && (llx >= x2[floor] || lly >= y2[floor] || urx <= x1[floor] || ury <= y1[floor])) {
		floor += 1;
	}
	if (floor > N) {
		area[c] += (urx-llx) * (ury-lly);
		return;
	}
	if (llx < x1[floor]) {
		cover(llx, lly, x1[floor], ury, floor+1, c);
		llx = x1[floor];
	}
	if (lly < y1[floor]) {
		cover(llx, lly, urx, y1[floor], floor+1, c);
		lly = y1[floor];
	}
	if (urx > x2[floor]) {
		cover(x2[floor], lly, urx, ury, floor+1, c);
		urx = x2[floor];
	}
	if (ury > y2[floor]) {
		cover(llx, y2[floor], urx, ury, floor+1, c);
		ury = y2[floor];
	}

}

int main(int argc, char ** argv)
{
	FILE* fin = fopen("rect1.in", "r");
	fout = fopen("rect1.out", "w");
	fscanf(fin, "%d %d %d", &x2[0], &y2[0], &N);
	memset(area, 0, sizeof(area));
	memset(color, 0, sizeof(color));
	color[0] = 1;
	x1[0] = 0;
	y1[0] = 0;
	for (int i=1; i<=N; ++i) {
		fscanf(fin, "%d %d %d %d %d", &x1[i], &y1[i], &x2[i], &y2[i], &color[i]);
	}
	for (int i=N; i>=0; --i) {
		cover(x1[i], y1[i], x2[i], y2[i], i+1, color[i]);
	}
	for (int i=1; i<2501; ++i) {
		if (area[i]) {
			printf("%d %d\n", i, area[i]);
			fprintf(fout, "%d %d\n", i, area[i]);
		}
	}

	return 0;
}

