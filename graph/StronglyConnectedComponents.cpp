// 強連結成分分解
typedef struct StronglyConnectedComponents {
	int n, group = 0;
	vector<vector<int>>& g;
	vector<vector<int>> rg;
	vector<int> compo, order;
	vector<bool> seen;

	StronglyConnectedComponents(vector<vector<int>>& g) : n(g.size()), g(g), rg(n), compo(n, -1), seen(n) {
		for (int i = 0; i < n; i++) {
			for (auto&& to : g[i]) {
				rg[to].emplace_back(i);
			}
		}
		build();
	}

	int operator[](int k) { return compo[k]; }

	vector<vector<int>> dag() {
		vector<vector<int>> dag(group);
		for (int i = 0; i < n; i++) {
			for (auto&& to : g[i]) {
				int s = compo[i], t = compo[to];
				if (s != t) dag[s].emplace_back(t);
			}
		}
		// 多重辺を落とす
		for (auto&& v : dag) {
			sort(v.begin(), v.end());
			v.erase(unique(v.begin(), v.end()), v.end());
		}
		return dag;
	}

	// 各成分にどの頂点が属しているか
	vector<vector<int>> groups() {
		vector<vector<int>> res(group);
		for (int i = 0; i < n; i++) {
			res[compo[i]].emplace_back(i);
		}
		return res;
	}

private:
	void build() {
		for (int i = 0; i < n; i++) {
			if (seen[i]) continue;
			dfs(i);
		}
		reverse(order.begin(), order.end());
		for (auto&& i : order) {
			if (compo[i] == -1) {
				rdfs(i);
				group++;
			}
		}
	}
	// 非再起dfs
	void dfs(int cur) {
		stack<pair<int, bool>> st;
		st.emplace(cur, true);
		while (!st.empty()) {
			auto [v, f] = st.top();
			st.pop();
			if (f) {
				if (seen[v]) continue;// 多重辺を落とす
				seen[v] = true;
				st.emplace(v, false);
				for (auto&& nv : g[v]) {
					if (seen[nv]) continue;
					st.emplace(nv, true);
				}
			}
			else order.emplace_back(v);
		}
	}

	void rdfs(int cur) {
		compo[cur] = group;
		stack<int> st;
		st.emplace(cur);
		while (!st.empty()) {
			auto v = st.top();
			st.pop();
			for (auto&& nv : rg[v]) {
				if (compo[nv] != -1) continue;
				compo[nv] = group;
				st.emplace(nv);
			}
		}
	}

	/* 再起dfs
	void dfs(int v) {
		seen[v] = 1;
		for (auto&& nv : g[v]) {
			if (seen[nv]) continue;
			dfs(nv);
		}
		order.emplace_back(v);
	}

	void rdfs(int v, int& cur) {
		compo[v] = cur;
		for (auto&& nv : rg[v]) {
			if (compo[nv] != -1) continue;
			rdfs(nv, cur);
		}
	}
	*/
} SCC;
