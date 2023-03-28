// 重み付きグラフ
auto weighted_graph(int n, int m, bool directed = 0, int origin = 1) {
	struct Edge {
		int to; ll w;
		Edge(int to, ll w) : to(to), w(w) {}
	};
	vector<vector<Edge>> g(n);
	while (m--) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		u -= origin, v -= origin;
		g[u].emplace_back(Edge(v, w));
		if (!directed) g[v].emplace_back(Edge(u, w));
	}
	return g;
}

