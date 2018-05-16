//Date : 08 - 03 - 18	//Author : Rishabh Paul
 
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
#define LEFT(i) 2*i + 1
#define RIGHT(i)	2 *i + 2
using namespace std;
using namespace __gnu_pbds;
typedef tree<	int,	null_type,	less<int>,	rb_tree_tag,	tree_order_statistics_node_update>
ordered_set;
const int N = 100005;
map<int ,ordered_set> M;
int m[4 * N] ,a[N];
set<int> S[4 * N];
void build(int i ,int s,int e){
	if(s > e)	return;
	if(s == e){
		S[i].clear();
		S[i].insert(a[s]);	
		m[i] = a[s];
		return;
	}
	int q = (s + e) / 2;
	build(LEFT(i) ,s ,q);
	build(RIGHT(i) ,q + 1 ,e);
	S[i].clear();
	for(int j = s ; j <= e ; j++)	S[i].insert(a[j]);
	m[i] = max(m[LEFT(i)] ,m[RIGHT(i)]);
}
int get(int i ,int s ,int e ,int l ,int r){
	if(s > e || e < l || s > r)	return 0;
	if(s >= l && e <= r)	return m[i];
	int q = (s + e) / 2;
	return max(get(LEFT(i) ,s ,q,l ,r) ,get(RIGHT(i) ,q + 1 ,e ,l ,r));
}
void update(int i ,int s,int e,int id ,int x){
	if(s > e || id < s || id > e)	return;
	if(s == e){
		if(id == s){
			S[i].erase(S[i].find(a[id]));
			S[i].insert(x);
			m[i]  = x;
		}
		return;
	}
	int q = (s + e) / 2;
	update(LEFT(i) ,s ,q ,id ,x);
	update(RIGHT(i) ,q + 1 ,e ,id ,x);
	m[i] = max(m[LEFT(i)] ,m[RIGHT(i)]);
	int xx = M[a[id]].order_of_key(s);
	int yy = M[a[id]].order_of_key(e + 1) ,cx;
	cx = yy - xx;
	if(cx == 1)	S[i].erase(S[i].find(a[id]));
	S[i].insert(x);
}
int query(int i ,int s,int e ,int l ,int r ,int x){
	if(s > e || e < l || s > r)	return 0;
	if(s >= l && e <= r){
		set<int> :: iterator it = S[i].lower_bound(x);
		if(it == S[i].begin())	return 0;
		return *(--it);
	}	
	int q = (s + e) / 2;
	return max(query(LEFT(i) ,s ,q ,l ,r ,x) , query(RIGHT(i) ,q + 1 ,e ,l ,r ,x));
}
/*void printM(){
	for(auto it : M){
		printf("%d\n" ,it.first);
		ordered_set :: iteartor itt = it.second.begin();
		while(itt != it.second.end())	printf("%d " ,*itt);
		printf("\n");
	}
}*/
int main(){
	int n ,Q ,t ,l ,r;
	scanf("%d %d" ,&n ,&Q);
	M.clear();
	for(int i = 0 ; i < n ; i++){
		scanf("%d" ,&a[i]);
		M[a[i]].insert(i);
	}
	//printM();
	build(0 ,0 ,n - 1);
	while(Q--){
		scanf("%d %d %d" ,&t ,&l ,&r);
		if(t == 1){
			update(0 ,0 ,n - 1 ,l - 1 ,r);
			M[a[l - 1]].erase(l - 1);
			M[r].insert(l - 1);
			a[l - 1] = r;
		}else{
			int x ,y ,z ,xx ,yy ,cx;
			z = get(0 ,0 ,n - 1 ,l - 1 ,r - 1);
			xx = M[z].order_of_key(l - 1);
			yy = M[z].order_of_key(r);
			cx = yy - xx;
			if(cx >= 3)	printf("%lld\n" ,3LL * z);
			else{
				if(cx == 2)	y = z;
				else y = query(0 ,0 ,n - 1 ,l - 1 ,r - 1 ,z);
				if(y == z){
					x = query(0 ,0 ,n - 1 ,l - 1 ,r - 1 ,y);
				}else{
					xx = M[y].order_of_key(l - 1);
					yy = M[y].order_of_key(r);
					cx = yy - xx;
					if(cx >= 2)	x = y;
					else x = query(0 ,0 ,n - 1 ,l - 1 ,r - 1 ,y);
				}
				bool fff = 0;
				while(x){
					//printf("%d %d %d\n" ,x ,y ,z);
					if(x + y > z){
						fff = 1;
						printf("%lld\n" ,0LL + x + y + z);
						break;
					}
					z = y;
					y = x;
					if(y == z){
						xx = M[y].order_of_key(l - 1);	yy = M[y].order_of_key(r);	cx = yy - xx;
						if(cx >= 3){
							fff = 1;	printf("%lld\n" ,3LL * y);	break;
						}else	x = query(0 ,0 ,n - 1 ,l - 1 ,r - 1 ,y);
					}else{
						xx = M[y].order_of_key(l - 1);	yy = M[y].order_of_key(r);	cx = yy - xx;
						//printf("%d %d %dyy " ,xx ,yy ,cx);
						if(cx >= 2)	x = y;
						else x = query(0 ,0 ,n - 1 ,l - 1 ,r - 1 ,y);
					}
				}
				if(!fff)	puts("0");
			}
		}
	}
	return 0;
} 