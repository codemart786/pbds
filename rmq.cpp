//Date: 13-06-2021 //Author: Rishabh Paul

#include<bits/stdc++.h>
using namespace std;
#define pb(a) push_back(a)



/*
	Application of sparse table data structure. Sparse table can be used to efficiently answer queries, like range min
	queries. Segment trees are also good data strutures to answer the same, when we have online updates, but without updates
	time complexity to answer per query reduces to O(1) with sparse table, whereas with segment trees it is O(lg N).

	Practice Problem: https://www.spoj.com/problems/RMQSQ/

*/
struct RMQ {
	int n; //no of elements
	vector<int> a;
	int LOG;
	vector<vector<int>> m;

	RMQ(vector<int> &b) { //only allocate memories
		init(b);
	}

	void init(vector<int> &b) {
		a = vector<int>(b);
		n = b.size();
		LOG = 0;
		while((1 << LOG) <= n) LOG++;
	}

	void build() { //build sparse table, left this to user, after reading doc, O(N * lg N ) time
		m = vector<vector<int>>(n, vector<int>(LOG));
		//2 ^ 0 = 1, element range
		for (int i = 0; i < n; i++) m[i][0] = a[i];
		for (int j = 1; j < LOG; j++)
			for (int i = 0; i + (1 << j) - 1 < n; i++)
				m[i][j] = min(m[i][j - 1], m[i + (1 << (j - 1))][j - 1]);
	}

	//returns min element with [l..r] range in O(1) time
	int query(int L, int R) {
		int length = R - L + 1;
		int k = 31 - __builtin_clz(length);
		return min(m[L][k], m[R - (1 << k) + 1][k]);
	}
};

int main () {

	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	vector<int> a(n);
	for (int &x :a) cin >> x;

	RMQ rmq(a);
	rmq.build(); //build the sparse table

	int Q;
	cin >> Q;

	while(Q--) {
		int l, r;
		cin >> l >> r; //already 0 based indexing
		cout << rmq.query(l, r) << "\n";
	}
	return 0;
}

