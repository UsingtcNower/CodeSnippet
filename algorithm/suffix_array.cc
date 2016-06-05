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
#include <functional>

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


// owner: nowerzt@gmail.com
class SuffixArray {
	vector<vector<int> > bucket;
	vector<int> suffix;
	int N, L, K;
	const string& str;
	void suffix_sort();
	void update_bucket();

	bool less_than(int a, int b) { 
		if(K==0) return str[a]<str[b];
		else {
			if(bucket[K-1][a]==bucket[K-1][b]) return bucket[K-1][a+L/2]<bucket[K-1][b+L/2];
			else return bucket[K-1][a]<bucket[K-1][b];
		}
	}

	inline bool equal(int a, int b) {
		return !less_than(a,b) && !less_than(b,a);
	}

	public:
	explicit SuffixArray(const string& s) : N(SZ(s)), L(0), K(0), str(s) { suffix_sort();}
	// return the sorted suffix
	int operator [] (int i) { return suffix[i];}
	// Given two suffixs of string, return the longest common prefix length
	int lcp_length(int x, int y);
};

void SuffixArray::suffix_sort() {
	// init suffix
	suffix.resize(N);
	for(int i=0;i<N;i++) suffix[i]=i;
	// init bucket
	bucket.resize(ceil(log2(N))+1);
	for(size_t k=0;k<bucket.size();k++) bucket[k].resize(N+N);
	
	for(L=1,K=0;(L>>1)<N;L<<=1,K++) {
		sort(suffix.begin(), suffix.end(), bind(&SuffixArray::less_than, *this, placeholders::_1, placeholders::_2));
		update_bucket();
	}
}


void SuffixArray::update_bucket() {
	int seq=0;
	bucket[K][suffix[0]]=0;
	for(int i=1;i<N;i++) {
		if(!equal(suffix[i],suffix[i-1])) seq++;
		bucket[K][suffix[i]]=seq;
	}
	fill(bucket[K].begin()+N, bucket[K].end(), -1);
}
// 1. the max substr length that occurs at least K times, solution: substr len = lcp(suffix[i], suffix[i+K-1]), for all i<=N-K
// 2. the max substr length that occurs only K times? solution: max(lcp(suffix[i],suffix[i+K])+1,lcp(suffix[i], suffix[i+K-1])), for all i<=N-K
// 3. the min substr length that occurs only K times? 
int SuffixArray::lcp_length(int x, int y) {
	if(x==y) return N-x;
	int ret=0;
	for(int k=K-1;k>=0 && x<N && y<N;k--) {
		if(bucket[k][x]==bucket[k][y]) {
			x += (1<<k);
			y += (1<<k);
			ret += (1<<k);
		}
	}
	return ret;
}

void print(string::iterator b, string::iterator e) {
	for(auto it=b;it!=e;++it) cout<<*it;
}

int
main()
{
	string str;
	while(cin>>str) {
		SuffixArray sa(str);
		cout<<"final:"<<endl;
		rep(i,0,SZ(str)) {
			print(str.begin()+sa[i], str.end());
			cout<<endl;
		}
		
		int i=rand()%SZ(str);
		int j=rand()%SZ(str);
		print(str.begin()+i,str.end());
		cout<<" ";
		print(str.begin()+j,str.end());
		cout<<" "<<sa.lcp_length(i,j)<<" ";
		print(str.begin()+i, str.begin()+i+sa.lcp_length(i,j));
		cout<<endl;
	}
}
