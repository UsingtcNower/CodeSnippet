#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <numeric>
#include <algorithm>

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

template <class T> T Abs(T x) {return x<0?-x:x;}

// Z[i] is the length of the longest substring starting from S[i] which is also a prefix of S, S index start from 0
vi z;
void Zalg(const string& s) {
	int n=s.size();
	z.resize(n);
	z[0]=n;
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
  		if (i > R) {
    			L = R = i;
    			while (R < n && s[R-L] == s[R]) R++;
    			z[i] = R-L; R--;
  		} else {
    			int k = i-L;
    			if (z[k] < R-i+1) z[i] = z[k];
    			else {
      				L = i;
      				while (R < n && s[R-L] == s[R]) R++;
      				z[i] = R-L; R--;
    			}
  		}
	}
}

int
main()
{
	string str;
	while(cin>>str) {
		int N=SZ(str);
		Zalg(str);
		vi cnt(N+1,0);
		for(int i=N-1;i>=0;i--) cnt[z[i]]++;
		int sum=cnt[N];
		for(int i=N-1;i>=0;i--) {
			if(cnt[i]!=0) {
				int pre=sum;
				sum += cnt[i];
				cnt[i] += pre;
			}
		}
		vector<pair<int,int> > ans;
		for(int i=N-1;i>=0;i--) {
			// S[i...N-1] is also a prefix
			if(z[i]==N-i) ans.pb(make_pair(z[i],cnt[z[i]]));
		}
		cout<<SZ(ans)<<endl;
		rep(i,0,SZ(ans)) cout<<ans[i].first<<" "<<ans[i].second<<endl;
	}
	return 0;
}
