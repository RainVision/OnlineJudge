#include <stdio.h>
#include <string.h>

inline int min(int a, int b) { return a < b ? a : b; };

const int MAX = 100000;
const int MAX_SEG = MAX << 2 | 10;
const int MAX_INT = 1 << 30;
struct node {
	int left, right;
	int value;
	int dirty;
};

struct node seg[MAX_SEG] = {0};
int a[MAX];
int len;

void build(int n, int l, int r){
	seg[n].left = l;
	seg[n].right = r;
	seg[n].dirty = 0;
	if(l == r){
		seg[n].value = a[l];
	}else{
		build(n*2, l, (l+r)/2);
		build(n*2+1, (l+r)/2+1, r);
		
		seg[n].value = min(seg[n*2].value, seg[n*2+1].value);
	}
}

int query(int n, int l, int r){
	if(seg[n].left > r || seg[n].right < l){
		//����������Сֵ��ʹ��һ��trick 
		return MAX_INT;	
	}
	
	if(l <= seg[n].left && seg[n].right <= r){
		//�����Ҷ�ӽڵ㣬ֱ�ӷ��أ����ٸ��µ��鷳 
		return (seg[n].left == seg[n].right) ? a[seg[n].left] : seg[n].value;
	}
	int v1, v2;
	v1 = query(n*2, l, r);
	v2 = query(n*2+1, l, r);
	return min(v1, v2);
}

//�������ϸ��� (����Խ�磬��Ϊÿһ����Ҷ�ӽڵ㶼������������)
void updateUp(int n){
	if(n == 1) {
		return;
	}
	int p = n / 2;
	seg[p].value = min(seg[p*2].value, seg[p*2+1].value);
	updateUp(p);
}


//�������(use 'Dirty' mark) 
void update(int n, int l, int r){
	if(l <= seg[n].left && seg[n].right <= r){
		if(seg[n].left == seg[n].right){
			seg[n].value = a[seg[n].left]; 
		}else{
			seg[n].value = min(seg[n*2].value, seg[n*2+1].value);
			seg[n].dirty = 1;
		}
		return;
	}
	int mid = (seg[n].left+seg[n].right)/2;
	if(l < mid){
		update(seg[n].left, l, r);	
	}
	if(r > mid){
		update(seg[n].right, l, r);	
	}
	updateUp(n);
}

int main(void){
	freopen("SegmentTree.in", "r", stdin);
	
	scanf("%d", &len);
	for(int i=0;i<len;i++){
		scanf("%d", &a[i]);
	}
	
	build(1, 0, len);
	
	int left = 0;
	int right = 5;
	printf("query(%d, %d)=%d\n", left, right, query(1, left, right));
	
	return 0;
}
