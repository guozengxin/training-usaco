/*
ID: gzxabcd1
PROG: maze1
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <memory.h>
#include <string>

const int dx1[4] = {1, -1, 0, 0}; 
const int dy1[4] = {0, 0, 1, -1}; 
const int dx2[4] = {2, -2, 0, 0};
const int dy2[4] = {0, 0, 2, -2};

int maze[210][80];
int step[2][210][80];
int W, H;
std::vector<std::string> lines;

void floodfill(int x, int y, int flag)
{
	int x1, y1, x2, y2;

	for (int i=0; i < 4; ++i) {
		x1 = x + dx1[i];
		y1 = y + dy1[i];
		x2 = x + dx2[i];
		y2 = y + dy2[i];
		if (x2 > 0 && x2 < 2 * H && y2 > 0 && y2 < 2 * W) {
			if (maze[x1][y1] == 1 && maze[x2][y2] == 1) {
				if (step[flag][x][y] + 1 < step[flag][x2][y2]) {
					step[flag][x2][y2] = step[flag][x][y] + 1;
					floodfill(x2, y2, flag);
				}
			}
		}
	}
}

int justifyx(int x)
{
	if (x == 0)
		return x+1;
	else if (x == H*2) 
		return x-1;
	return x;
}
int justifyy(int y)
{
	if (y == 0)
		return y+1;
	else if (y == W*2) 
		return y-1;
	return y;
}

int main(int argc, char ** argv)
{
	FILE* fin = fopen("maze1.in", "r");
	FILE* fout = fopen("maze1.out", "w");
	fscanf(fin, "%d %d", &W, &H);
	fprintf(stderr, "%d %d\n", W, H);
	char temp[10];
	fgets(temp, sizeof(temp), fin);
	for (int i=0; i < H*2+1; i++) {
		char line[80];
		fgets(line, sizeof(line), fin);
		lines.push_back(std::string(line));
	}

	int x1 = -1;
	int x2 = -1;
	int y1 = -1;
	int y2 = -1;
	for (int i=0; i < H*2+1; i++) {
		for (int j=0; j < W*2+1; j++) {
			maze[i][j] = 0;
			step[0][i][j] = 999999;
			step[1][i][j] = 999999;
			if (lines[i][j] == ' ') {
				if (i == 0 || j == 0 || i == H*2 || j == W*2) {
					maze[i][j] = 2;
					if (x1 == -1) {
						x1 = i;
						y1 = j;
					} else {
						x2 = i;
						y2 = j;
					}
				} else {
					maze[i][j] = 1;
				}
			}
		}
	}
	x1 = justifyx(x1);
	x2 = justifyx(x2);
	y1 = justifyy(y1);
	y2 = justifyy(y2);
	step[0][x1][y1] = 1;
	step[1][x2][y2] = 1;
	floodfill(x1, y1, 0);
	floodfill(x2, y2, 1);

	int ans = 0;
	for (int i=0; i < H*2+1; i++) {
		for (int j=0; j < W*2+1; j++) {
			if (((i&1)) && ((j&1))) {
				int tmp = step[0][i][j] > step[1][i][j] ? step[1][i][j] : step[0][i][j];
				if (tmp > ans) {
					ans = tmp;
				}
			}
		}
	}

	fprintf(fout, "%d\n", ans);

}
