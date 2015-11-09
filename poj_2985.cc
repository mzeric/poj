/*
	POJ 2985 Treap 平衡树

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <vector>

const int maxn = 300100;
#define IMAX INT_MAX;
int father[maxn];
int father_size[maxn];

int key[maxn], priority[maxn];
int childs[maxn][2], cnt[maxn], size[maxn], root, tot;


int find(int x){
	return x==father[x]?x:father[x]=find(father[x]);
}

//
void update(int x){
	size[x] = size[childs[x][0]] + cnt[x] + size[childs[x][1]];
}
void rotate(int &root, int left){
	int y = childs[root][left];
	childs[root][left] = childs[y][1-left];
	childs[y][1-left] = root;

	update(root);
	update(y);

	root = y;
}
	
	
void _insert(int &x, int k){
	if(x){
		if(key[x] == k)
			cnt[x]++;
		else{
			int t = key[x] < k;
			_insert(childs[x][t], k);
			if(priority[childs[x][t]] < priority[x])
				rotate(x, t);
		}

	}else{
		x = ++tot;
		key[x] = k;
		cnt[x] = 1;
		size[x] = 1;
		priority[x] = rand();
		childs[x][0] = childs[x][1] = 0;

		
	}
	update(x);
}

void _erase(int &x, int k){
	if(key[x]!=k){
		_erase(childs[x][key[x] < k], k);
	}else{
		if(cnt[x]>1)
			cnt[x]--;
		else{
			if(childs[x][0] == 0 && childs[x][1] == 0){
				x = 0;
				return;
			}
			int t = priority[childs[x][0]] > priority[childs[x][1]];
			rotate(x, t);
			_erase(x, k);

		}
	}

	update(x);
}
void insert(int k){
	_insert(root, k);
}
void erase(int k){
	_erase(root, k);

}
int _getkth(int &x, int k){
	if(k <= size[childs[x][0]])
		return _getkth(childs[x][0], k);

	k -= size[childs[x][0]]+cnt[x];
	if(k <=0 )
		return key[x];
	return _getkth(childs[x][1], k);

}
int _getkth_max(int x, int k){
	return _getkth(x, size[x] - k + 1);
}
int getkth(int k){
	return _getkth(root, k);
}
int total;
void input(int a, int b){
	int x = find(a);
	int y = find(b);
	if(x == y){
		return ;
	}
	erase(father_size[x]);
	erase(father_size[y]);

	father[y] = x;
	father_size[x] = father_size[x] + father_size[y];
	
	insert(father_size[x]);
	total--;
}

int query(int k){
	int x = getkth(total-k+1);
	return x;

}
void init(int n){
	for(int i = 0; i <= maxn; i++)
		father[i] = i;
	for(int i = 0; i <= maxn; i++)
		father_size[i] = 1;

	root = 0;
	tot = 0;
	priority[0] = IMAX;
	size[0]=0;
	total = n;

	for(int i = 1; i <= n; i++)
		insert(1);
}
int main(int argc, char *argv[]){

	int N, M;
	scanf("%d%d", &N, &M);
	init(N);

	while(M--){

		int t;
		scanf("%d", &t);
		if(t){
			int k;
			scanf("%d", &k);
			printf("%d\n", query(k));
		}else{
			int a, b;
			scanf("%d%d", &a, &b);
			input(a, b);
		}

	}
	
	return 0;
}
