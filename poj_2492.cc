/*
	POJ 2492 
	久违的并查集
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


bool ans;
const int maxn = 2005;
int father[maxn];
int opp[maxn];
int rank[maxn];

int find(int a){
	return father[a] = father[a] == a?a:find(father[a]);
}
void join(int a, int b){
	int x = find(a);
	int y = find(b);
	if(rank[a] < rank[b])
		father[x] = y;
	else{
		father[y] = x;
		if(rank[x] == rank[y])
			rank[a]++;
	}
}
void take(int a, int b){
	int x = find(a);
	int y = find(b);
	if(x == y){
		ans = true;
		return;
	}
	if(opp[a]){
		join(opp[a], b);
	}
	if(opp[b]){
		join(opp[b], a);
	}
	opp[a] = b;
	opp[b] = a;
}



int main(){
	int total;
	scanf("%d", &total);
	for(int s = 1; s <= total; s++){
		int n, m;
		scanf("%d%d", &n, &m);

		ans = false;
		for(int i = 0; i < maxn; i++){
			father[i] = i;
		}
		memset(opp, 0, sizeof(opp));
		memset(rank, 0, sizeof(rank));
		
		while(m--){
			int a, b;
			scanf("%d%d", &a, &b);
			take(a, b);
		}
		if(ans)
			printf("Scenario #%d:\nSuspicious bugs found!\n\n", s);
		else
			printf("Scenario #%d:\nNo suspicious bugs found!\n\n", s);

	}

	return 0;
}