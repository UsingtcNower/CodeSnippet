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
//#include <limits.h>
//#include <stdint.h>

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
#define bj(stat,b) (stat & (1LL<<b))
#define bc(stat,b) (stat & (~(1LL<<b)))
#define vi vector<int> 
#define vs vector<string>

template <class T> T Abs(T x) {return x<0?-x:x;}

#define maxDigit 32
#define maxB 2
#define maxS (1000000*(maxDigit+1)+1)
#define newNode() (MP+ML++)


struct trieNode {
	trieNode *nxt[maxB];
}MP[maxS];

int ML;

trieNode* root;

void init() {
	ML=0;
	root=newNode();
	memset(root,NULL, sizeof(trieNode));
}

void insert(ll x) {
	//ll u=x;
	//int digit[maxDigit+1];
	//mem (digit, 0);
	//int jin=0;
	//while(u) {
	//	digit[jin++]=(u&1);
	//	u >>= 1;
	//}
	//cout<<x<<" ";
	//for(int i=maxDigit;i>=0;i--) cout<<digit[i];
	//cout<<endl;
	//cout<<endl;
	//rep(i,0,SZ(digit)) cout<<digit[i];
	//cout<<endl;
	trieNode* p = root;
	for(int i=maxDigit;i>=0;i--) {
		int digit=bj(x,i)>>i;
		if(p->nxt[digit]==NULL) {
			p->nxt[digit]=newNode();
			memset(p->nxt[digit], NULL, sizeof(trieNode));
		}
		p=p->nxt[digit];
	}
}

ll query(ll x) {
	ll ans=0;
	
	//rep(i,0,SZ(digit)) cout<<digit[i];
	//cout<<endl;
	//for(int i=maxDigit;i>=0;i--) cout<<digit[i];
	//cout<<endl;

	trieNode* p = root;
	for(int i=maxDigit;i>=0;i--) {

		int wei=i;
		int digit=bj(x,i)>>i;
		if(p->nxt[1-digit]!=NULL) {

			if((1-digit)) ans |= (1LL<<wei);
			p=p->nxt[1-digit];
			//cout<<wei<<" "<<digit[i]<<" "<<p->nxt[1-digit[i]]<<" "<<1-digit[i]<<" "<<ans<<" "<<(1LL<<wei)<<endl;
		} else {
			if(digit) ans |= (1LL<<wei);
			p=p->nxt[digit];
			//cout<<wei<<" "<<digit[i]<<" "<<p->nxt[digit[i]]<<" "<<digit[i]<<endl;
		}
	}

	return ans;
}

