#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <numeric>
#include <algorithm>
#include <stack>
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

#define MOD 1000000007
#define MAXN 100001
int N;
vi w;

typedef vector<vector<int> > Graph;

class DGraphSCC {
	private:
		stack<int> sk;
		vi seq;
		vi belong;

		Graph g;
		int N, cur;
		vi LOW;
		vector<bool> instack;

	public:
		DGraphSCC(const Graph& __g) : g(__g), N(__g.size()), cur(0) {
			instack.resize(N);
			LOW.resize(N);
			belong.resize(N);
			seq.resize(N);
			fill(ALL(seq), 0);
			fill(ALL(instack), false);		
		

			rep(i,0,N) {
				if(!seq[i]) tarjan(i);
			}
		}
	
		void tarjan(int u) {
			LOW[u]=seq[u]=++cur;	
			sk.push(u);
			instack[u]=true;
			rep(i,0,g[u].size()) {
				int v=g[u][i];
				if(!seq[v]) {
					tarjan(v);
					LOW[u]=min(LOW[u],LOW[v]);
				} else if(instack[v] && seq[v]<seq[u]) {
					LOW[u]=min(LOW[u],seq[v]);
				}
			}
			if(LOW[u]==seq[u]) {
				while(sk.top()!=u) {
					belong[sk.top()]=u;
					instack[sk.top()]=false;
					sk.pop();
				}
				belong[sk.top()]=u;
				instack[sk.top()]=false;
				sk.pop();
			}
		}

		int operator [](int i) { return belong[i]; }

};

int
main()
{
	while(cin>>N) {
		Graph g(N);
		w.resize(N);
		
		rep(i,0,N) cin>>w[i];
		int u,v;
		int M;
		rep(i,0,N) g[i].clear();
		cin>>M;
		rep(i,0,M) {
			cin>>u>>v;
			u--;
			v--;
			g[u].pb(v);
		}
		DGraphSCC gscc(g);
		ll tot_cost=0;
		int tot_num=1;
		vector<int> scc[N];
		rep(i,0,N) {
			scc[gscc[i]].pb(i);
		}
		rep(i,0,N) {
			if(SZ(scc[i])>0) {
			int min_w=1000000010;
			int num=0;
			rep(j,0,SZ(scc[i])) {
				if(w[scc[i][j]]<min_w) {
					min_w=w[scc[i][j]];
					num=1;
				} else if(w[scc[i][j]]==min_w) {
					num++;
				}
			}
			tot_cost += min_w;
			tot_num = ((ll)tot_num*(ll)num)%MOD;
			}
		}
		cout<<tot_cost<<" "<<tot_num<<endl;
	}
}
