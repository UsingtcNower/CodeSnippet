#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <numeric>

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <limits.h>

using namespace std;

typedef long long ll;

#define mem(a,b) memset(a,b, sizeof a)
#define SZ(x)	(int)x.size()
#define FOREACH(it,x) for(__typeof((x).begin()) it=(x.begin());it!=(x.end());++it)
#define ERR 1e-5
#define PI (2.0*acos(0))
#define ALL(x) x.begin(),x.end()
#define pb push_back
#define rep(i,n,m) for(int i = (int)n,_m=(int)m;i<_m;++i)
#define bj(stat,b) (stat & (1<<b))
#define bc(stat,b) (stat & (~(1<<b)))
#define vi vector<int> 
#define vs vector<string>

#define popc(i) (__builtin_popcountll(i))
// i should not be zero
#define low_bit_index(i) (__builtin_ctz(i))
#define high_bit_index(i) (sizeof(i)*8-1-__builtin_clz(i))
#define last_bit(i) (i&~(i-1))

template <class T> T Abs(T x) {return x<0?-x:x;}
#define MAXN 1010
struct DSU {
	int p[MAXN];

	void init(int n) {
		for(int i=0;i<=n+1;i++) p[i]=i;
	}
	int find(int x) {
		while(x!=p[x]) x=p[x];
		return x;
	}
	void merge(int x, int y) {
		p[find(x)]=p[find(y)];
	}
};

int a[MAXN][MAXN];
int U[MAXN][MAXN],D[MAXN][MAXN],L[MAXN][MAXN],R[MAXN][MAXN];
int N,M,Q;
int b[MAXN], seq[MAXN];

bool cmp(int x, int y) {
	return b[x]<b[y];
}

int rec(int x, int n) {
	for(int i=1;i<=n;i++) seq[i]=i;
	sort(seq+1,seq+1+n, cmp);
	DSU lf,rt;
	lf.init(n);
	rt.init(n);
	int ans=0;
	for(int i=n;i>=1;i--) {
		int l=lf.find(seq[i]);
		int r=rt.find(seq[i]);
		if(x>=l && x<=r) ans=max(ans, (r-l+1)*b[seq[i]]);
		lf.merge(seq[i]+1,seq[i]);
		rt.merge(seq[i]-1,seq[i]);
	}
	return ans;
}

int
main()
{
	while(cin>>N>>M>>Q) {
		rep(i,1,N+1) rep(j,1,M+1) cin>>a[i][j];

		// pre-process for U,D,L,R
		mem (U,0);
		mem (D, 0);
		mem (L, 0);
		mem (R, 0);

		for(int i=1;i<=N;i++) for(int j=1;j<=M;j++) {
			if(a[i][j]) {
				U[i][j]=U[i-1][j]+1;
				L[i][j]=L[i][j-1]+1;
			} else {
				U[i][j]=0;
				L[i][j]=0;
			}
		}
		for(int i=N;i>=1;i--) for(int j=M;j>=1;j--) {
			if(a[i][j]) {
				D[i][j]=D[i+1][j]+1;
				R[i][j]=R[i][j+1]+1;
			} else {
				D[i][j]=0;
				R[i][j]=0;
			}
		}


		int op,x,y;
		rep(t,0,Q) {
			cin>>op>>x>>y;
			if(op==1) {
				a[x][y] ^= 1;
				rep(i,x,N+1) {
					if(a[i][y]) U[i][y]=U[i-1][y]+1;
					else U[i][y]=0;
				}
				for(int i=x;i>=1;i--) {
					if(a[i][y]) D[i][y]=D[i+1][y]+1;
					else D[i][y]=0;
				}
				for(int j=y;j<=M;j++) {
					if(a[x][j]) L[x][j]=L[x][j-1]+1;
					else L[x][j]=0;
				}
				for(int j=y;j>=1;j--) {
					if(a[x][j]) R[x][j]=R[x][j+1]+1;
					else R[x][j]=0;
				}
			} else if(op==2) {
				int ans=0;
				for(int j=1;j<=M;j++) b[j]=D[x][j];
				ans = max(ans, rec(y,M)); //Down
				for(int j=1;j<=M;j++) b[j]=U[x][j];
				ans = max(ans, rec(y,M)); //UP
				for(int i=1;i<=N;i++) b[i]=L[i][y];
				ans = max(ans, rec(x,N));
				for(int i=1;i<=N;i++) b[i]=R[i][y];
				ans = max(ans, rec(x,N));
				cout<<ans<<endl;
			}
		}
	}
}
