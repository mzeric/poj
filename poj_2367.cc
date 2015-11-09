/*
        poj 2367
        auth mzeric
        直接的拓扑排序
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <vector>
#include <queue>
#include <string.h>
#include <iostream>

using namespace std;

const int MAXN = 105;

/* 前向星 */
int info[MAXN*2];
int to[MAXN*2];
int gn[MAXN*2];

int num = 0;
void add_edge(int i, int j){
        num++;
        to[num] = j;
        gn[num] = info[i];
        info[i] = num;
}
int main(){
        int i,n;
        cin>>n;
        i = 0;
        vector<int> g[MAXN];
        queue<int> q;
        int ins[MAXN];
        int L[MAXN];
        int tot = 0;
        memset(ins, 0, sizeof(ins));
        memset(info, 0, sizeof(info));
        memset(to, 0, sizeof(to));
        memset(gn, 0, sizeof(gn));

        while(i++ < n){
                int a;

                while(scanf("%d", &a),a){
                        g[i].push_back(a);
                        add_edge(i, a);

                        ins[a]++;
                }
                
        }

        for(int i = 1; i<=n; i++)
                if(!ins[i])
                        q.push(i);

        while(!q.empty()){
                int u = q.front();q.pop();
                L[tot++] = u;
                for(int e = info[u]; e; e = gn[e]){
                        int t = to[e];
                        ins[t]--;
                        if(!ins[t])
                                q.push(t);
                }
        }
        for(int i = 0; i < n; i++)
                printf("%d ", L[i]);
        printf("\n");
}