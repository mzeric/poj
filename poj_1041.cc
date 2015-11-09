/*
	POJ 1041
	欧拉回路，最小升序


	Euler 模板：深搜，有重复的边、自环，所以要区分边，用边的编号，前向星
			邻接表 适合对边排序

	dfs(int x){
		for each next 点: y{
			if(vis[边])
				continue;
			vis[边] = 1;
			dfs(y);
			path.push_back(边(x-y));
		}
	}
	实际输出的是 path的倒序

*/

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>


using namespace std;

const int maxn = 1995;
const int maxm = 1000000;
vector< pair<int, int> > adj[maxn];
int vis[maxm];

int fa[maxn];

/*

前向星结构

*/

int head[man];
int to[maxm*2];
int link[maxm*2];
int index = 0;

void add_edge(int x, int y, int z){
	index++;

	to[index] = y;
	link[index] = head[x];
	head[x] = index;
}

#define CLR(x) memset((x), 0, sizeof((x)))


#define eid first
#define vtx second

void add(int x, int y, int z){
	
	adj[x].push_back(make_pair(z, y));
	adj[y].push_back(make_pair(z, x));
}

int get_fa(int x){
	
	return x == fa[x]?x:fa[x] = get_fa(fa[x]);
}
void dfs(int x, vector<int> &path){
	
	for(int i = 0; i < adj[x].size(); ++i){
		int e = adj[x][i].eid;
		int y = adj[x][i].vtx;
		if(vis[e])
			continue;
		vis[e] = 1;
		dfs(y, path);
		path.push_back(e);
	}
}
void init(){
        for(int i = 0; i < maxn; i++)
                adj[i].clear();
        memset(fa, 0, sizeof(fa));
		CLR(head);CLR(to);CLR(link);
		index = 0;
}
bool solve(vector<int> &path){

	/* 判断 连通性 */
	for(int i = 0; i < maxn; i++)
		fa[i] = i;
	for(int i = 0; i < maxn; i++){
		for(int j = 0; j < adj[i].size(); j++)
			fa[get_fa(i)] = get_fa(adj[i][j].vtx);

	}

	int origin = -1;
	for(int i = 1; i < maxn; i++){
		if(adj[i].empty())
			continue;
		if(adj[i].size()%2 == 1) return false;
		if(origin == -1)
				origin = i;
		if(get_fa(i) != get_fa(origin)) return false;

		sort(adj[i].begin(), adj[i].end());
	}

	if(origin == -1) return false;

	path.clear();
	memset(vis, 0, sizeof(vis));

	dfs(origin, path);
	reverse(path.begin(), path.end());

	return true;
}

int main(){
	
	int x,y,z;
	while(scanf("%d%d", &x, &y)){
		if(x == 0 && y == 0)
			break;
		scanf("%d", &z);
		init();
		add(x, y, z);
		while(scanf("%d%d", &x, &y)){
			if(x == 0 && y == 0)
				break;
			scanf("%d", &z);
			add(x, y, z);
		}

		vector<int> path;
		
		if(!solve(path)){
			printf("Round trip does not exist.\n");
		}else{
			int i;
			for(i = 0; i < path.size()-1; i++)
				printf("%d ", path[i]);
			printf("%d\n", path[i]);
		}
	}


	return 0;
}

