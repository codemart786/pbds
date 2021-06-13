/*

	Concept of Binary Lifting in Trees
	This can be useful in
		finding lca of two nodes in a tree
		finding kth ancestor of any node v in a tree
	This reduces the time complexity to logarithmic, O(log(depth of tree)), instead of O(depth of tree)

	Practice Question: https://leetcode.com/problems/kth-ancestor-of-a-tree-node/
*/


#include<bits/stdc++.h>
using namespace std;
#define pb push_back

struct LCA {

	int n; //nodes
	int LOG; //log of n, for binary lifting
	vector<vector<int>> a; //tree
	vector<int> depth; //depth array of tree
	vector<int> p; //parent array of tree
	vector<vector<int>> anc; //ancestor of the vertices
	LCA(int n = 0) { //constructor
		init(n);
	}

	void init(int _n) {
		n = _n;
		LOG = 0;
		while((1 << LOG) <= n) LOG++;
		a = vector<vector<int>>(n, vector<int>());
		depth = vector<int>(n, 0);
		p = vector<int>(n);
		anc = vector<vector<int>>(n ,vector<int>(LOG));
	}

	void add_edge(int u, int v) {
		a[u].pb(v);
		a[v].pb(u);
	}

	void dfs(int s, int pr) {
		p[s] = pr;
		if (s) depth[s] = depth[pr] + 1;
		for (int x: a[s]) {
			if (x == pr) continue;
			dfs(x, s);
		}
	}

	void b_lift() {
		for (int i = 0; i < n; i++) anc[i][0] = p[i];
		for (int i = 0; i < n; i++)
			for (int j = 1; j < LOG; j++)
				anc[i][j] = anc[ anc[i][j - 1] ][j - 1];
	}

	int get_lca(int a, int b) {
		if (depth[a] < depth[b]) {
			swap(a, b); //a is the more deeper node;
		}
		int k = depth[a] - depth[b];
		//kth ancestor of a
		for (int j = 0; j < LOG; j++) {
			if (k & (1 << j)) a = anc[a][j];
		}
		if (a == b) { //which means a and b falls in a line
			return a;
		}
		for (int j = LOG - 1; j >= 0; j--) {
			if (anc[a][j] != anc[b][j]) {
				a = anc[a][j];
				b = anc[b][j];
			}
		}
		//parent of a, or parent b
		//return p[a];
		return anc[a][0];
	}
};

int main () {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, e; //no of nodes and edges
	cin >> n;
	e = n - 1;
	LCA lca(n);

	while(e--) {
		int u,v;
		cin >> u >> v;
		u--, v--;
		lca.add_edge(u, v);
		lca.add_edge(v, u);
	}

	lca.dfs(0, 0); //for populating p and depth arrays
	lca.b_lift(); //for populating ancestors arrays

	int Q;
	cin >> Q;

	while(Q--) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		cout << 1 + lca.get_lca(a, b) << "\n";
	}
	return 0;
}
