/*

	POJ 1182

*/

#include <stdlib.h>
#include <vector>
#include <string.h>
#include <stdio.h>


int N,K;

const int maxn = 5005;
const int maxk = 100005;

int father[maxn];
int vis[maxn];
int up[maxn];
int down[maxn];

int fcount = 0;
void find(int u){
	if(u == father[u])
		return u;
	int t = father[u];
	father[u] = find(father[u]);
	
	up[u] = up[father[u]];
	down[u] = down[father[u]];


	return f[u];
}
void un(int u, int v){
	int a = find(u);
	int b = find(v);

	father[a] = b;

}
void add(int type, int a, int b){
	if(type == 1){
		if(vis[a] && vis[b]){
			if(find(a) != find(b)){
				fcount++;
				return;
			}
		}else{
			vis[a] = vis[b] = 1;
			un(a, b);
		
		}

	}else{

	}

}

void init(){
	for(int i = 0; i < maxn; i++){
		father[i] = i;
		child[i] = i;
	}
	memset(vis, 0, sizeof(vis));
}

int main()
{
	scanf("%d%d", &N, &K);
	init();
	while(k--){
		int type, a, b;
		scanf("%d%d%d", &type, &a, &b);
		if( (type == 2 && a == b) || a > N || b > N){
			fcount++;
			continue;
		}
		add(type, a, b);

	}
	
	return 0;
}
