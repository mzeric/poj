/*
        POJ 1330 LCA
        在线和离线两种算法
        前向星 to和next数组下标要同步
        

*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

const int maxn = 10001;
vector<int> head;
vector<int> enext;
vector<int> to;
int vis[maxn];
int p[maxn];
int in[maxn];

int cnt = 0;

int qa, qb, lca;
vector<int> que;
#define CLR(x) memset((x), 0, sizeof(x));
void init(int n){
        head.clear();
        enext.clear();
        to.clear();
        to.push_back(0);
        enext.push_back(0);

        CLR(vis);
        CLR(in);

        qa = qb = 0;
        for(int i = 0; i<= n; i++)
                p[i] = i;
        lca = -1;
}
void expand(int i){
        if(head.size() < i+2)
                head.resize(i+2);
}

void add_edge(int i, int j){
        expand(i);expand(j);
        to.push_back(j);
        enext.push_back(head[i]);
        
        head[i] = to.size()-1;

}
int find(int u){
        if(p[u] == u)
                return u;
        return p[u] = find(p[u]);
}
void tarjan_lca(int u){
        p[u] = u;
        vis[u] = 1;

        for(int e = head[u]; e; e = enext[e]){
                int v = to[e];
                if(!vis[v]){
                        tarjan_lca(v);
                        p[v] = u;
                }
        }
        if(u == qa && vis[qb]){
                lca = find(qb);
        }else if(u == qb && vis[qa]){

                lca = find(qa);
        }
}
int main(){

        int cases = 0;
        scanf("%d", &cases);
        while(cases--){
                int n;

                scanf("%d", &n);
                init(n);
                for(int i = 0; i < n-1; i++){
                        int a,b;
                        scanf("%d%d", &a, &b);
                        add_edge(a, b);
                        in[b]++;
                }
                scanf("%d%d", &qa, &qb);
                
                int t;
                for(t = 1; t <= n; t++)
                        if(in[t] == 0)
                                break;
                tarjan_lca(t);
                printf("%d\n", lca);
        }
}

