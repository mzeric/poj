/*      poj_1502
*/

#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
const int MAXN = 105;
int matrix[MAXN][MAXN];
int dist[MAXN];
int path[MAXN];
int vis[MAXN];
const int INF = 1<<30;


int info[MAXN*2];
int to[MAXN*2];
int gnext[MAXN*2];
int w[MAXN*2];

int num = 0;
void add_edge(int i, int j, int v){
        num++;
        to[num] = j;
        gnext[num] = info[i];
        info[i] = num;
        w[num] = v;
}

int dijstra(int n){
        int start, min_dist;
        fill_n(dist, MAXN, INF);
        fill_n(vis, MAXN, 0);

        dist[1] = 0;
        start = 1;

        for(int m = 1; m <= n; ++m){


                /* find the min */

                min_dist = INF;
                int u = 0;
                for(int j = 1; j <= n; ++j){
                        if(!vis[j] && min_dist > dist[j]){
                                u = j;
                                min_dist = dist[j];
                        }
                }
                vis[u] = 1;
                path[u] = start;
                start = u;
                /* loose adj */
                for(int j = 1; j <= n; ++j){
                        if(matrix[u][j] < 0)
                                continue;
                        if(!vis[j]&&dist[j] > dist[u] + matrix[u][j]){
                                dist[j] = dist[u] + matrix[u][j];
                        }
                }
        }

        return min_dist;

}

/* 前向星 */
int dijstra_fs(int n){
        fill_n(vis, MAXN, 0);
        fill_n(dist, MAXN, INF);
        dist[1] = 0;

        int m = 1;
        for(int i = 1; i <=n; i++){
                int min_dis = INF;
                for(int e = info[m]; e; e = gnext[e]){
                        int u = to[e];
                        if(!vis[u] && min_dis > dist[u]){
                                min_dis = dist[u];
                                m = u;
                        }
                }
                vis[m] = 1;
                for(int e = info[m]; e; e = gnext[e]){
                        int u = to[e];
                        if(!vis[u] && dist[u] > dist[m] + w[e])
                                dist[u] = dist[m] + w[e];
                }
        }
        //cout<<"前向星"<<endl;
}
/* 邻接表 */
vector<pair<int, int> > g[MAXN+10];
int dijstra_g(int n){
        fill_n(dist, MAXN, INF);
        dist[1] = 0;
        int m = 1;
        for(int i = 1; i <=n; ++i){
                int min_dis = INF;

                for(int s = 0; s < g[m].size(); ++s){
                        int u = g[m][s].first;
                        if(!vis[u] && min_dis > dist[u]){
                                m = u;
                                min_dis = dist[u];
                        }
                }
                vis[m] = 1;

                for(int s = 0; s < g[m].size(); ++s){
                        int u = g[m][s].first;
                        int w = g[m][s].second;
                        if(!vis[u] && dist[u] > dist[m] + w){
                                dist[u] = dist[m] + w;
                        }
                }
        }
}
int spfa(int n){
        queue<int> q;
        q.push(1);
        bool inq[MAXN];
        fill_n(inq, MAXN, false);
        inq[1] = true;
        fill_n(dist, MAXN, INF);
        dist[1] = 0;

        while(!q.empty()){

                int u = q.front();q.pop();

                for(int i = 0; i < g[u].size(); ++i){
                        int v = g[u][i].first;
                        if(dist[v] > dist[u] + g[u][i].second){
                                dist[v] = dist[u] + g[u][i].second;
                                if(!inq[v]){
                                        inq[v] = true;
                                        q.push(v);
                                }
                        }
                }

                inq[u] = false;

        }
        //cout<<"spfa"<<endl;
}
int main(){
        char s[MAXN];
        int n = 0;
        memset(matrix, 0, sizeof(int)*MAXN*MAXN);
        memset(info, 0, MAXN*2*sizeof(int));
        memset(to, 0, MAXN*2*sizeof(int)) ;
        memset(gnext, 0, MAXN*2*sizeof(int));
        while(cin>>n){
                for(int i = 2; i <= n; ++i){
                        for(int j = 1; j <i; ++j){
                                cin>>s;
                                if(!strcmp(s, "x"))
                                        matrix[i][j] = matrix[j][i] = -1;
                                else{
                                        g[i].push_back(make_pair(j, atoi(s)));
                                        g[j].push_back(make_pair(i, atoi(s)));

                                        add_edge(i, j, atoi(s));
                                        add_edge(j, i, atoi(s));
                                        matrix[i][j] = matrix[j][i] = atoi(s);
                                }
                        }
                }
                //dijstra_fs(n);
                spfa(n);
                int ret = 0;
                for(int i = 1; i<=n; ++i){
                        if(dist[i] > ret)
                                ret = dist[i];
                }
                cout<<ret<<endl;
        }
}
int main2(int argc, char *argv[])
{
    int i,j;
    char ch[100];
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        for(i=2;i<=n;i++)
        {
                for(j=1;j<=i-1;j++)
                {
                    scanf("%s",ch);
                    if(ch[0]=='x')
                    matrix[i][j]=matrix[j][i]=INF;
                    else
                    matrix[i][j]=matrix[j][i]=atoi(ch);               
                }
        }
        for(i=1;i<=n;i++)
        {
             matrix[i][i]=0;
        }

       dijstra_g(n);
           int ret = 0;
                for(int i = 1; i<=n; ++i){
                        if(dist[i] > ret)
                                ret = dist[i];
                }
                cout<<ret<<endl;
    }
    return EXIT_SUCCESS;
}