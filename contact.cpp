/*
ID: gzxabcd1
PROG: contact
LANG: C++
*/
#include <stdio.h>
#include <memory.h>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

FILE *fout;
int A, B, N;
std::map<std::string, int> mresult;

void parsestr(std::string str, int llen) {
	int len = str.length();
	std::string s;
	for (int i=A; i<=len; ++i) {
		for (int j=llen-i+1; j<=len-i; ++j) {
			s.assign(str, j, i);
			if (mresult.find(s) == mresult.end()) {
				mresult[s] = 1;
			} else {
				mresult[s] += 1;
			}
		}
	}
}

struct Result {
	int freq;
	std::vector<std::string> list;
};

std::vector<Result> final;

bool cmp(std::string s1, std::string s2) {
	if (s1.length() != s2.length()) {
		return s1.length() < s2.length();
	} else {
		return s1 < s2;
	}
}

void addResult(const std::string& str, int freq) {
	bool ok = false;
	int i;
	for (i=0; i<final.size(); ++i) {
		if (freq == final[i].freq) {
			final[i].list.push_back(str);
			ok = true;
		} else if (freq < final[i].freq) {
			continue;
		} else if (freq > final[i].freq) {
			break;
		}
	}
	if (!ok) {
		Result r;
		r.freq = freq;
		r.list.push_back(str);
		final.insert(final.begin()+i, r);
	}
}

int main(int argc, char ** argv)
{
	FILE* fin = fopen("contact.in", "r");
	fout = fopen("contact.out", "w");
	fscanf(fin, "%d %d %d", &A, &B, &N);
	char c;
	std::string laststr;
	while (fscanf(fin, "%c", &c) != -1) {
		if (c != '0' && c != '1') {
			continue;
		}
		int len = laststr.length();
		if (len < A) {
			laststr.push_back(c);
			if (len + 1 >= A) {
				parsestr(laststr, len);
			}
		} else if (len >= A) {
			if (len == B) {
				laststr.assign(laststr, 1, B-1);
				len = len-1;
			}
			laststr.push_back(c);
			parsestr(laststr, len);
		}
	}
	std::map<std::string, int>::iterator itr;
	for (itr=mresult.begin(); itr!=mresult.end(); ++itr) {
		addResult(itr->first, itr->second);	
	}
	for (int i=0; i<final.size(); ++i) {
		if (i>=N) {
			break;
		}
		fprintf(fout, "%d\n", final[i].freq);
		sort(final[i].list.begin(), final[i].list.end(), cmp);
		int len = final[i].list.size();
		for (int j=0; j<len; ++j) {
			char sep = ' ';
			if (j == len-1 || (j+1)%6 == 0) {
				sep = '\n';
			}
			fprintf(fout, "%s%c", final[i].list[j].c_str(), sep);
		}
	}

	return 0;
}

