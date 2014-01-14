/*
ID: gzxabcd1
PROG: fracdec
LANG: C++
*/
#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <vector>

FILE *fout;

int main(int argc, char ** argv)
{
	FILE* fin = fopen("fracdec.in", "r");
	fout = fopen("fracdec.out", "w");
	int N, D;
	fscanf(fin, "%d %d", &N, &D);

	char result[100000];
	int len = snprintf(result, 100000, "%d.", N/D);
	int leftpart = N % D;
	int r = leftpart;
	char decimal[100002] = {0};
	int dsize = 0;
	bool flag[100002] = {false};
	int lefts[100002] = {0};
	int cycle = -1;
	int idx = 0;
	while (r!=0) {
		if (flag[r]) {
			cycle = lefts[r];
			break;
		}
		if (cycle >= 0) {
			break;
		}
		flag[r] = true;
		lefts[r] = idx;
		idx += 1;
		r = r * 10;
		decimal[dsize] = r / D;
		dsize += 1;
		r = r % D;
	}
	int i;
	for (i=0; i<dsize; ++i) {
		if (i == cycle) {
			len += snprintf(result+len, 100000-len, "(");
		}
		len += snprintf(result+len, 100000-len, "%d", decimal[i]);
	}
	if (i == 0) {
		len += snprintf(result+len, 100000-len, "0");
	}
	if (cycle >= 0) {
		len += snprintf(result+len, 100000-len, ")");
	}
	result[len] = '\0';
	for (i=0; i<strlen(result); ++i) {
		fprintf(fout, "%c", result[i]);
		if ((i+1)%76 == 0) {
			fprintf(fout, "\n");
		}
	}
	if (i%76 != 0) {
		fprintf(fout, "\n");
	}

	return 0;
}

