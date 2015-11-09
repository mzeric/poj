/*
	POJ 1056 Trie

*/
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

const int maxn = 10000;
int child[maxn][2];
int end[maxn];
bool flag;

vector<vector<int> > childv;
int tot;
int root;

void init(){
	tot = 1;
	root = 1;

	childv.clear();
	//childv.push_back(vector<int>[2]);
	//childv.push_back(vector<int>[2]);

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
	int i = 1;
	char str[1024];
	init();
	while(scanf("%s", str)!= EOF){
		if(*str == '9'){
			if(!solve()){
				printf("Set %d is immediately decodable\n", i);
			}else{
				printf("Set %d is not immediately decodable\n", i);
			}
			i++;
			init();
		}

		insert(str);

	}
	return 0;
}
