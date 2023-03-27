#pragma once

// グラフ
vector<vector<int>> graph(int n, int m, bool directed = 0, int origin = 1) {
	vector<vector<int>> g(n);
	while (m--) {
		int u, v;
		cin >> u >> v;
		u -= origin, v -= origin;
		g[u].emplace_back(v);
		if (!directed) g[v].emplace_back(u);
	}
	return g;
}
