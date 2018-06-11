//Date : 11 - 06 - 18  //Author : Rishabh Paul

/**
*	The following program is implementation of 2D - Segment Trees . 
*	Input : n * m 2D Array (Standard Input)
*	Query : sum of sub-rectangle whose upper-left corner is<r1 ,c1> and lower-right corner is<r2 ,c2> (Standard Output)
*	Update : a[r][c] = x 
*	Constraints : 0 <= r < n , 0 <= c < m , -1e9 <= x <= 1e9
*	Space : 4mn
* 	Query-Time : O(lgn(n) * lg(m))	, where lg is logarithm base 2
*	0-based indexing everywhere
*/

#include<bits/stdc++.h>
using namespace std;

#define LEFT(i) 2 * (i) + 1
#define RIGHT(i) 2 * (i) + 2

int n ,m;	//Size of grid

void build(std::vector<int> &seg ,const std::vector<int> &a ,int i ,int s ,int e) {
	if(s > e)	return;
	if(s == e) {
		seg[i] = a[s];
		return;
	}
	int q = (s + e) / 2;
	build(seg ,a ,LEFT(i) ,s ,q);
	build(seg ,a ,RIGHT(i) ,q + 1 ,e);
	seg[i] = seg[LEFT(i)] + seg[RIGHT(i)];
}

void build(std::vector<std::vector<int>> &seg ,const std::vector<std::vector<int>> &a ,int i ,int s ,int e) {
	if(s > e)	return;
	if(s == e) {
		build(seg[i] ,a[s] ,0 ,0 ,m - 1);
		return;
	}
	int q = (s + e) / 2;
	build(seg ,a ,LEFT(i) ,s ,q);
	build(seg ,a ,RIGHT(i) ,q + 1 ,e);
	for(int j = 0 ; j < 2 * m ; j++)	seg[i][j] = seg[LEFT(i)][j] + seg[RIGHT(i)][j];
}
int query(const std::vector<int> &seg ,int i ,int s ,int e ,int l ,int r) {
	if(e < l || s > e || r < s)	return 0;
	if(s >= l && e <= r)	return seg[i];
	int q = (s + e) / 2;
	return query(seg ,LEFT(i) ,s ,q ,l ,r) + query(seg ,RIGHT(i) ,q + 1 ,e ,l ,r);
}
int query(const std::vector<std::vector<int>> &seg ,int i ,int s ,int e ,int r1 ,int c1 ,int r2 ,int c2) {
	if(r2 < s || r1 > e || s > e)	return 0;
	if(s >= r1 && e <= r2) {
		return query(seg[i] ,0 ,0 ,m - 1 ,c1 ,c2);
	}
	int q = (s + e) / 2;
	return query(seg ,LEFT(i) ,s ,q ,r1 ,c1 ,r2 ,c2) + query(seg ,RIGHT(i) ,q + 1 ,e ,r1 ,c1 ,r2 ,c2);
}
void update(std::vector<int> &seg ,std::vector<int> &a ,int i ,int s ,int e ,int id ,int x) {
	if(s > e || id < s || id > e)	return;
	if(s == e) {
		if(id == s) 	seg[i] = x ,a[s] = x;
		return;
	}
	int q = (s + e) / 2;
	update(seg ,a ,LEFT(i) ,s ,q ,id ,x);
	update(seg ,a ,RIGHT(i) ,q + 1 ,e ,id ,x);
	seg[i] = seg[LEFT(i)] + seg[RIGHT(i)];
}
void update(std::vector<std::vector<int>> &seg ,std::vector<std::vector<int>> &a ,int i ,int s ,int e ,int r ,int c ,int x) {
	if(s > e || r < s || r > e)	return;
	if(s == e) {
		if(s == r) update(seg[i] ,a[s] ,0 ,0 ,m - 1 ,c ,x);
		return;
	}
	int q = (s + e) / 2;
	update(seg ,a ,LEFT(i) ,s ,q ,r ,c ,x);
	update(seg ,a ,RIGHT(i) ,q + 1 ,e ,r ,c ,x);
	for(int j = 0 ; j < 2 * m ; j++)	seg[i][j] = seg[LEFT(i)][j] + seg[RIGHT(i)][j];
}
int main() {
	int Q ,t ,r1 ,c1 ,r2 ,c2;
	scanf("%d %d" ,&n ,&m);
	std::vector<std::vector<int>> a(n ,std::vector<int>(m)) ,seg(2 * n ,std::vector<int>(2 * m , 0));
	for(int i = 0 ; i < n ; i++)	
		for(int j = 0 ; j < m ; j++)	scanf("%d" ,&a[i][j]);
	build(seg ,a , 0 ,0 ,n - 1);
	scanf("%d" ,&Q);
	while(Q--) {
		scanf("%d %d %d %d" ,&t ,&r1 ,&c1 ,&r2);
		if(t == 0) {
			scanf("%d" ,&c2);
			printf("%d\n" ,query(seg ,0 ,0 ,n - 1 ,r1 ,c1 ,r2 ,c2));
		} else	update(seg ,a ,0 ,0 ,n - 1 ,r1 ,c1 ,r2);
	}
	return 0;
}