

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <iostream>
    #include <vector>


    using namespace std;

    const int MAXN = 110;
    int num = 0;
    int info[MAXN];
    int to[10005];
    int link[10005];

    int low[MAXN];
    int dfn[MAXN];
    int vis[MAXN];

    int cut[MAXN];
	vector<int> vv[MAXN];

vector<int> head;
vector<int> h_to;
vector<int> h_next;

void expand(int i){
	if(head.size() < i + 1)
		head.resize(i+1);
}
void add_edge_2(int i, int j){
	expand(i);expand(j);
	h_to.push_back(j);
	h_next.push_back(head[i]);
	head[i] = h_to.size()-1;
}
    void add_edge(int i, int j){
            num++;
            to[num] = j;
            link[num] = info[i];
            info[i] = num;
    }

    void cut_bridge(int cur, int parent, int dep, int n){
            vis[cur] = 1;
            dfn[cur] = low[cur] = dep;

            int child = 0;
            for(int e = info[cur]; e; e = link[e]){
                    int u = to[e];
                    if(u != parent && vis[u] == 1){/* 祖先 */
							low[cur] = min(low[cur], dfn[u]);
                    }
                    if(!vis[u]){
                            /* dfs 到底 */
                            cut_bridge(u, cur, dep+1, n);
                            child++;
    						low[cur] = std::min(low[cur], low[u]);
                            if((cur == 1 && child >1) || (cur != 1 && low[u] >= dfn[cur])){
                                    cut[cur] = 1;
                            }

                    }else{
						low[cur] = min(low[cur], dfn[u]);
					}
            }

    }



    void init(int n){
            memset(info, 0, sizeof(info));
            memset(to, 0, sizeof(to));
            memset(link, 0, sizeof(link));

            memset(low, 0, sizeof(low));
            memset(dfn, 0, sizeof(dfn));
            memset(vis, 0, sizeof(vis));
			memset(cut, 0, sizeof(cut));

			num = 0;


    }

    int get_cut(int n){



            cut_bridge(1, -1, 0, n);
    		
            int ret = 0;
            for(int i = 1; i <= n; i++){
                    if(cut[i])
                            ret++;
            }

            return ret;
    }

int main()
{
	int n;
	while(scanf("%d",&n)==1&&n)
	{
		int a,b;
		int i,ans=0;
		char c;
		init(n);
		while(scanf("%d",&a)==1&&a)
		{
			while((c=getchar())!='\n')
			{
				scanf("%d",&b);
				add_edge(a, b);
				add_edge(b, a);
			}
		}

		cut_bridge(1,-1,0,n);

		printf("%d\n",get_cut(n));
	}
	return 0;
}
