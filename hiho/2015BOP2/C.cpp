#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAX = 110000;

struct user {
	int sex;
	vector<int> v;	
};

struct bian {
	int u1, u2;
	int w;	
};

struct user a[MAX];
struct bian b[MAX];
int blen;
long long _count;

void debug(){
	for(int i=0;i<blen;i++){
		printf("i=%d u1=%d [%d] u2=%d [%d] w=%d\n", i+1, b[i].u1, a[b[i].u1].sex, b[i].u2, a[b[i].u2].sex, b[i].w);
	}
	printf("count=%lld\n", _count);
}

void changebian(int x, int y, int z){
	//find
	int i, j, len, old;
	bool finded = false;
	len = a[x].v.size();
	for(i=0;i<len;i++){
		int t = a[x].v[i];
		if((b[t].u1 == x && b[t].u2 == y ) || (b[t].u2 == x && b[t].u1 == y)){
			old = b[t].w;
			b[t].w = z;
			finded = true;
			break;
		}
	}
	if(finded){
		if(a[x].sex != a[y].sex){
			_count += (z - old);
		}
	}else{
		//add
		b[blen].w = z;
		b[blen].u1 = x;
		b[blen].u2 = y;
		a[x].v.push_back(blen);
		a[y].v.push_back(blen);
		if(a[x].sex != a[y].sex){
			_count += z;	
		}
		blen+=1;
	}
}

void solution(){
	int n, m, q, i, j, k, x, y, z;
	memset(a, 0, sizeof(a));
	blen = 0;
	_count = 0;
	
	scanf("%d %d %d", &n, &m, &q);
	for(i=1;i<=n;i++){
		scanf("%d", &a[i].sex);
		a[i].v.clear();
	}
	for(i=0;i<m;i++){
		scanf("%d %d %d", &x, &y, &z);
		b[blen].w = z;
		b[blen].u1 = x;
		b[blen].u2 = y;
		a[x].v.push_back(blen);
		a[y].v.push_back(blen);
		if(a[x].sex != a[y].sex){
			_count += z;	
		}
		blen+=1;
	}
	for(i=0;i<q;i++){
		scanf("%d", &x);
		if(x == 1){
			scanf("%d", &y);
			a[y].sex = 1 - a[y].sex;
			//update 
			int lll = a[y].v.size();
			for(j=0;j<lll;j++){
				int t = a[y].v[j];
				int other;
				if(b[t].u1 == y){
					other = b[t].u2;
				}else{
					other = b[t].u1;	
				}
				if(a[y].sex == a[other].sex){
					_count -= b[t].w;
				}else{
					_count += b[t].w;	
				}
				//printf("%d %d %d\n", b[t].u1, b[t].u2, b[t].w);
				//printf("%d %d\n", y, other);
				//debug();
			}
			
		}else if(x == 2){
			scanf("%d %d %d", &x, &y, &z);
			changebian(x, y, z);
		}else if(x == 3){
			printf("%lld\n", _count);
		}
	}
}

int main(void){
	freopen("C.in", "r", stdin);
	int t, i;
	while(scanf("%d", &t)!=EOF){
		for(i=1;i<=t;i++){
			printf("Case #%d:\n", i);
			solution();
		}
	}
	return 0;
}
