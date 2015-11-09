/*
	POJ 3264 Interval Tree

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

#define MAX ((50000<<2))
const int INF = 0x7fffffff;




	//vector<int> top;
	//vector<int> cover;
	int top[MAX],down[MAX],cover[MAX];
	int size;

	int nMax, nMin;


void init(int n){
	memset(top,0, sizeof(top));
	memset(down, 0, sizeof(down));
	size = n;
}

	
	void _query(int a, int b, int ll, int rr, int ind, int *mm, int *mi){

		if(a<=ll && rr <= b){
			*mm = top[ind];
			*mi = down[ind];
			return;
		}
		int mid = (ll + rr)/2;
		int mmax,mmin;

		if(a <= mid){
			_query(a, b, ll, mid, ind<<1, &mmax, &mmin);
			nMax = max(nMax, mmax);
			nMin = min(nMin, mmin);


		}
		if(mid < b){
			_query(a, b, mid+1, rr, (ind<<1)+1, &mmax, &mmin);
			nMax = max(nMax, mmax);
			nMin = min(nMin, mmin);

		}

		*mm = nMax;
		*mi = nMin;
		return;
	}
	int query(int a, int b){
		nMax = -INF;nMin = INF;
		int m, n;
		_query(a, b, 1, size, 1, &m, &n);
		return m-n;
	}
	void _modify(int a, int ll, int rr, int ind, int m){
		if(ll == rr && ll == a){
			top[ind] = m;
			down[ind]= m;
			return;
		}
		int mid = (ll + rr)/2;
		if(a <= mid)
			_modify(a, ll, mid, ind<<1, m);
		else
			_modify(a, mid+1, rr, (ind<<1)+1, m);

		top[ind] = max(top[ind<<1], top[(ind<<1)+1]);
		down[ind] = min(down[ind<<1], down[(ind<<1)+1]);
	}
	void modify(int a, int m){
		_modify(a, 1, size, 1, m);
	}

int main(){

	int n,q;
	scanf("%d%d", &n, &q);
	init(n);
	for(int i = 1; i <=n; i++){
		int v;
		scanf("%d", &v);
		modify(i, v);
	}

	while(q--){
		int a,b;
		scanf("%d%d", &a, &b);
		printf("%d\n", query(a, b));
	}
	return 0;
}
