/*
ID: gzxabcd1
PROG: nocows
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <memory.h>

using namespace std;

ifstream fin("nocows.in");
ofstream fout("nocows.out");

int dp[200][100];
int n,k;

int ped_num(int node,int height);

void solve()
{
    memset(dp,-1,sizeof(dp));

    dp[1][1] = 1;

    fin>>n>>k;

    fout<<(ped_num(n,k)-ped_num(n,k-1)+9901)%9901<<endl;
}

int ped_num(int node,int height)
{
    if(node%2!=1) return 0;

    if(height>(node+1)/2)
        height = (node+1)/2;

    if(dp[node][height]!=-1)
        return dp[node][height];

    int res = 0;

    for(int i=1;i<(node-1)/2;i+=2){
        res+=ped_num(i,height-1)*ped_num(node-1-i,height-1);
        res%=9901;
    }
    res*=2;
    int tmp = ped_num((node-1)/2,height-1);
    res+=tmp*tmp;
    res%=9901;

    dp[node][height] = res;
    return res;
}

int main(int argc,char *argv[])
{
    solve(); 
    return 0;
}
