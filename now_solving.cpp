int n;
cin >> n;
vs s(n), t(n);
vvi g(n);
rep(i, 0, n) {
    g[i].emplace_back(i);
}
vb seen(n), finished(n);
bool res = 0;
auto dfs = [&](auto f, int v) -> void {
    seen[v] = 1;
    for (auto nv : g[v]) {
        if (finished[nv]) continue;
        if (seen[nv] and not finished[nv]) {
            res = 1;
            return;
        }
        f(f, v);
        if (res) return;
    }
    finished[v] = 1;
};
