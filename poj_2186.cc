/*

	poj 2186

*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>


const int maxn = 10005;
const int maxm = 50005;

using namespace std;

int info[maxn];
int to[maxm];
int link[maxm];

int color_cnt = 1;
int color[maxn];
int du[maxn];

int dfn[maxn];
int low[maxn];
int vis[maxn];

vector<int> dfs_stack;

int num = 0;
int dep;

void add_edge(int x, int y){
	num++;
	to[num] = y;
	link[num] = info[x];
	info[x] =  num;
}

vector<int> dfs_color[maxn];

void dfs(int x){
	dep++;
	dfn[x] = low[x] = dep;
	
	dfs_stack.push_back(x);
	vis[x] = 1;

	for(int e = info[x]; e; e = link[e]){
		int y = to[e];
		if(!vis[y]){
			dfs(y);
			low[x] = min(low[x], low[y]);
		}else if(vis[y] == 1){
			low[x] = min(low[x], dfn[y]);
		}
	}

	if(low[x] == dfn[x]){
		while(dfs_stack.back() != x){
			int u = dfs_stack.back();
			color[u] = color_cnt;
			dfs_color[color_cnt].push_back(u);
			vis[u] = 2;
			dfs_stack.pop_back();
		}
		
		dfs_color[color_cnt].push_back(dfs_stack.back());
		color[dfs_stack.back()] = color_cnt++;
		vis[dfs_stack.back()] = 2;
		dfs_stack.pop_back();

	}

}
#define CLR(x) memset((x),  0, sizeof((x)))

void init(){

	CLR(color);
	CLR(vis);CLR(dfn);CLR(low);CLR(info);CLR(link);
	CLR(du);
}
int solve(int n, int m){

	color_cnt = 1;
	dep = 0;
	for(int i = 1; i <=n; i++){
		if(!vis[i])
			dfs(i);
	}

	for(int i = 1; i <= n; i++){
		for(int e = info[i]; e; e = link[e]){
			int y = to[e];
			if(color[i] != color[y]){
				du[color[i]]++;/* 缩点的出度 */
			}
		}
	}
	int c = 0;
	int cc = 0;
	for(int i = 1; i < color_cnt; i++){
		if(!du[i]){
			cc = i;
			c++;
		}
	}
	if(c > 1)
		return 0;

	c = 0;
	for(int i = 0; i < maxn; i++){
		if(color[i] == cc)
			c++;
	}
	return c;
}

int main(){



	int n, m;
	scanf("%d%d", &n, &m);
	int a, b;
	init();
	for(int i = 0; i < m; i++){
		scanf("%d%d", &a, &b);
		
		add_edge(a, b);
	}

	cout<<solve(n, m)<<endl;

}
