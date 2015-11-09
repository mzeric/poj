#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

const int maxp = 305;
const int maxn = 105;

vector<int> g[maxp];
int vis[maxn];


int main(int argc, char *argv[]){
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
