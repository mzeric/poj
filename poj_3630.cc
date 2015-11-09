/*
	POJ 1056 Trie

*/
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

const int maxn = 100000;
int child[maxn][10];
int end[maxn];
bool flag;

vector<vector<int> > childv;
int tot;
int root;

void init(){
	tot = 1;
	root = 1;


	flag = false;

	memset(child, 0, sizeof(child));
	memset(end, 0, sizeof(end));

}

bool solve(){
	return flag;
}

void insert(char *str){
	int *cur = &root;
	int new_ = 0;
	if(flag)
		return;
	for(const char *p = str; *p; p++){
		if(end[*cur]){
			flag = true;
		}
		cur = &child[*cur][*p-'0'];
		if(*cur == 0){
			new_ = 1;
			*cur = ++tot;
			memset(child[*cur], 0, sizeof(child[1]));

		}

	}
	if(new_ == 0)
		flag = true;

	end[*cur] = 1;

}

int main(int argc, char *argv[])
{

	int cases;
	scanf("%d", &cases);
	while(cases--){
		int n;
		scanf("%d", &n);
		init();
		while(n--){
			char str[1024] = {0};
			scanf("%s", str);
		

			insert(str);
		}

		if(solve()){
			printf("NO\n");
		}else{
			printf("YES\n");
		}

	}
	return 0;
}
