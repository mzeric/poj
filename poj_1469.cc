/*

	POJ 1469

	对p或者对n匹配都是可以的

*/


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string.h>


using namespace std;

const int maxn = 305;
const int maxp = 105;

vector<int> g[maxn];
int link[maxn];
int vis[maxn];



bool dfs(int x){
	for(int i = 0; i < g[x].size(); i++){
		int u = g[x][i];
		if(!vis[u]){
			vis[u] = 1;
			if(link[u] == -1 || dfs(link[u])){
				link[u] = x;
				return true;
			}
		}
	}
	return false;
}


int main(){
	int t;
	int n,p;
	int ans;
	scanf("%d", &t);
	while(t--){
		int n,p;
		scanf("%d%d",&p, &n);
		memset(g, 0, sizeof(g));
		for(int i = 0; i < maxn; i++)
			link[i] = -1;

		for(int i = 1; i <= p; i++){
			int m;
			scanf("%d", &m);
			int u;
			while(m--){
				scanf("%d", &u);
				g[i].push_back(u);
			}

		}

		int ans = 0;
		for(int i = 1; i <= p; i++){
			memset(vis, 0, sizeof(vis));
			if(dfs(i))
				ans++;
		}
		if(ans >= p)
			printf("YES\n");
		else
			printf("NO\n");


	}

	return 0;
}