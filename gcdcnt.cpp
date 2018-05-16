//Date : Sun Mar 03 16 : 28 : 30 2018
//Author : Rishabh Paul
 
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
#define LEFT(i) 2*i + 1
#define RIGHT(i)	2 *i + 2
using namespace std;
using namespace __gnu_pbds;
typedef tree<	int,	null_type,	less<int>,	rb_tree_tag,	tree_order_statistics_node_update>
ordered_set;
const int N = 100001;
int p[N] ,a[N];
vector<int> pdiv[N];
ordered_set divisors[N];
/*int ones[3 * N];
void build(int i ,int s ,int e){
	if(s > e)	return;
	if(s == e){
		if(a[s] == 1)	ones[i] = 1;
		else ones[i] = 0;
		return;
	}
	int q = (s + e) / 2;
	build(LEFT(i) ,s ,q);
	build(RIGHT(i) ,q + 1 ,e);
	ones[i] = ones[LEFT(i)] + ones[RIGHT(i)];
}
int get(int i ,int s ,int e ,int l ,int r){
	if(s > e || e < l ||s > r)	return 0;
	if(s >= l && e <= r)	return ones[i];
	int q = (s + e) / 2;
	return get(LEFT(i) ,s ,q ,l ,r) + get(RIGHT(i) ,q + 1 ,e,l ,r);
}
void update(int i ,int s ,int e ,int id ,int x){
	if(s > e || id < s || id > e)	return;
	if(s  == e){
		if(id == s){
			if(x == 1)	ones[i] = 1;
			else ones[i] = 0;
		}
		return;
	}
	int q = (s + e) / 2;
	update(LEFT(i) ,s ,q,id ,x);
	update(RIGHT(i) ,q + 1 ,e ,id ,x);
	ones[i] = ones[LEFT(i)]+ones[RIGHT(i)];
}*/
void pre(){
	p[0] = p[1] = 0;
	for(int i = 2 ; i < N ; i++)
		if(!p[i]){
			pdiv[i].push_back(i);
			for(int j = i * 2 ; j < N ; j += i){	pdiv[j].push_back(i);	p[j] = 1;	}
		}
}
void calc(int x ,int i ,int t){
	int j;
	for(j = 1 ; j * j < x ; j++){
			if(x % j == 0){
				if(!t){divisors[j].insert(i);	divisors[x / j].insert(i);}
				else{	divisors[j].erase(i);	divisors[x / j].erase(i);	}
			}
		}
		if(!t){	if(j * j == x)	divisors[j].insert(i);	}
		else{	if(j * j == x)	divisors[j].erase(i);	}
}
/*void printArray(int i){
	set<int>::iterator it = divisors[i].begin();
	while(it != divisors[i].end()){
		int x = *it;
		printf("yy%d " ,x);	++it;
	}
	printf("\n");
}*/
void init(){
	for(int i = 0 ; i < N ; i++){
		p[i] = 0;
		divisors[i].clear();
		pdiv[i].clear();
	}
}
int gcd(int a,int b){
	if(a==0)	return b;
	return gcd(b%a ,a);
} 

int main(){
	init();
	pre();
	int n ,x ,j;	scanf("%d" ,&n);
	for(int i = 0 ; i < n ; i++){
		scanf("%d" ,a + i);
		//if(a[i] == 1)	continue;
		calc(a[i] ,i ,0);
	}
	int Q ,l ,r ,t;
	scanf("%d" ,&Q);
	while(Q--){
		scanf("%d %d %d" ,&t ,&l ,&r);
		if(t == 2){
			scanf("%d" ,&x);
			if(x == 1){
				int tot =r - l + 1;
				printf("%d\n" ,tot);
			}else{
				int tot = r - l + 1,ans = 0 ,mm = pdiv[x].size();
				l--;
				//printf("%d " ,mm);
				for(int i = 1; i < (1 << pdiv[x].size()); i++){
					int f = 1 ,_1 = 0;
					for(j = 0 ; j < pdiv[x].size() ; j++){
						if(i & (1 << j)){
							_1++;
							f *= pdiv[x][j];
						}
					}
					int xx = divisors[f].order_of_key(l);
					int yy = divisors[f].order_of_key(r);
					//printf("%d %d " ,xx ,yy);
					if(yy >= xx){
						if(_1 & 1)	ans += yy - xx ;
						else ans -= yy - xx ;
						//printf("%d " ,ans);
					}
					
				}
				printf("%d\n" ,tot - ans);
			}
		}else{
			--l;
			calc(a[l] ,l ,1);
			calc(r ,l ,0);
			//if(a[l] == 1)	update(0 ,0 ,n - 1 ,l ,r);
			//if(r == 1)	update(0 ,0 ,n - 1 ,l ,r);
			a[l] = r;
		}
	}
	return 0;
}

/*
10
20 36 10 3 1 1 5 8 7 7
50
2 1 8 1
*/