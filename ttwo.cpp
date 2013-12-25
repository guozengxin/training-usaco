/*
ID: gzxabcd1
PROG: ttwo
LANG: C++
*/
#include <stdio.h>
#include <vector>
#include <string>

const int N = 10;
char g_grid[N][N];

class Status
{
private:
	int x;
	int y;
	int direction;
	char (*grid)[N];

public:
	Status(int x, int y, int d = 0);
	bool operator ==(const Status &s);
	bool equal(const Status &s);
	void setGrid(char grid[N][N]);
	bool step();
	std::string tostring();

protected:
	void move();
	void move_back();
	bool posvalid();
};

Status::Status(int x, int y, int d)
{
	this->x = x;
	this->y = y;
	this->direction = d;
}
std::string Status::tostring()
{
	char s[64];
	snprintf(s, sizeof(s), "%d %d %d", x, y, direction);
	return std::string(s);
}

bool Status::operator ==(const Status &s)
{
	return x == s.x && y == s.y && direction == s.direction;
}

bool Status::equal(const Status &s)
{
	return x == s.x && y == s.y;
}

void Status::setGrid(char grid[N][N])
{
	this->grid = grid;
}

bool Status::step() 
{
	int trytime = 0;
	while (true) {
		move();
		if (posvalid()) {
			return true;
		} else {
			move_back();
			direction = (direction + 1) % 4;
			return true;
		}
	}
}

void Status::move()
{
	switch(direction) {
	case 0:
		x -= 1;
		break;
	case 1:
		y += 1;
		break;
	case 2:
		x += 1;
		break;
	case 3:
		y -= 1;
		break;
	}
}

void Status::move_back()
{
	switch(direction) {
	case 0:
		x += 1;
		break;
	case 1:
		y -= 1;
		break;
	case 2:
		x -= 1;
		break;
	case 3:
		y += 1;
		break;
	}
}

bool Status::posvalid()
{
	if (x < 0 || x >= N || y < 0 || y >= N) {
		return false;
	} else if (grid[x][y] == '*') {
		return false;
	} else {
		return true;
	}
}

int main(int argc, char **argv)
{
	FILE *fin = fopen("ttwo.in", "r");
	FILE *fout = fopen("ttwo.out", "w");
	for (int i = 0; i < N; i ++) {
		fscanf(fin, "%s", g_grid[i]);
	}
	Status *farmer;
	Status *cow;
	for (int i = 0; i < N; i ++) {
		for (int j = 0; j < N; j ++) {
			if (g_grid[i][j] == 'C') {
				cow = new Status(i, j);
				g_grid[i][j] = '.';
			} else if (g_grid[i][j] =='F') {
				farmer = new Status(i, j);
				g_grid[i][j] = '.';
			}
		}
	}
	if (!farmer || !cow) {
		fprintf(stderr, "error\n");
		return -1;
	}
	farmer->setGrid(g_grid);
	cow->setGrid(g_grid);

	std::vector<Status> fstat;
	std::vector<Status> cstat;
	int steptime = 0;
	while (true) {
		//fprintf(stderr, "farmer %s cow %s\n", farmer->tostring().c_str(), cow->tostring().c_str());
		bool stop = false;
		for (int i = 0; i < fstat.size(); i ++) {
			if (fstat[i] == *farmer && cstat[i] == *cow) {
				stop = true;
				break;
			}
		}
		if (stop) {
			steptime = 0;
			break;
		}
		fstat.push_back(*farmer);
		cstat.push_back(*cow);
		if (cow->equal(*farmer)) {
			break;
		}
		cow->step();
		farmer->step();
		steptime += 1;
	}
	fprintf(fout, "%d\n", steptime);

	if (farmer) {
		delete farmer;
	}
	if (cow) {
		delete cow;
	}
	fclose(fin);
	fclose(fout);
}
