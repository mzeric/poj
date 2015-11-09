/*
	POJ 1056 Trie
	TLE

*/
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

bool flag;

vector<vector<int> > childv;
vector<int> end;
int root;

void init(){
	root = 1;

	childv.clear();
	end.clear();
	childv.push_back(vector<int>(10));
	childv.push_back(vector<int>(10));
	end.push_back(0);end.push_back(0);

	flag = false;

}

bool solve(){
	return flag;
}

void insert(char *str){
	int cur = root;
	int new_ = 0;
	for(const char *p = str; *p; p++){
		if(end[cur]){
			flag = true;
		}
		int t = cur;
		cur = childv[cur][*p-'0'];
		if(cur == 0){
			new_ = 1;
			childv.push_back(vector<int>(10));
			end.push_back(0);
			cur = childv.size() - 1;
			childv[t][*p-'0'] = cur;

		}

	}
	if(new_ == 0){
		flag = true;
	}

	end[cur] = 1;

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
