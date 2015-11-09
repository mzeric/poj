#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 1003;

int tree[maxn][maxn];
int n;

void init(){
	memset(tree, 0, sizeof(tree));
}

int lowbit(int x){
	return x&(-x);
}

void update(int x, int y){
	int i,j;
	for(int i = x; i <=n; i+= lowbit(i))
		for(int j = y; j <=n ; j+=lowbit(j))
			tree[i][j]++;
}

int query(int x, int y){
	int sum = 0;
	for(int i = x; i >0 ; i-=lowbit(i))
		for(int j = y; j > 0; j -= lowbit(j))
			sum += tree[i][j];

	return sum;
}
int main(int argc, char *argv[]){
	int x;
	scanf("%d", &x);
	while(x--){
		int t;
		scanf("%d%d", &n,&t);
		init();
		while(t--){
			char buf[16];
			scanf("%s", buf);
			if(buf[0] == 'C'){
				int x1, y1, x2, y2;
				scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
				update(x1, y1);
				update(x2+1, y2+1);
				update(x1, y2+1);
				update(x2+1, y1);

			}else{
				int x, y;
				scanf("%d%d", &x, &y);
				printf("%d\n", query(x, y)%2);

			}
		}
		printf("\n");
	}
	
	return 0;
}
