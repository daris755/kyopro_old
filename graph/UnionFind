struct UnionFind {
	vector<int> par, siz;

	// 初期化
	UnionFind(int n) : par(n, -1), siz(n, 1) { }

	// 根を求める(経路圧縮あり)
	int root(int x) {
		if (par[x] == -1) return x; // ｘが根の場合はｘを返す
		return par[x] = root(par[x]);
	}

	// ｘとｙが同じグループに属するかどうか（根が一致するかどうか）
	bool issame(int x, int y) {
		return root(x) == root(y);
	}

	// ｘを含むグループとｙを含むグループを併合する
	bool unite(int x, int y) {
		// ｘ，ｙをそれぞれ根まで移動する
		x = root(x);
		y = root(y);

		// すでに同じグループのときは何もしない
		if (x == y) return false;

		// union by size（ｙ側のサイズが小さくなるようにする）
		if (siz[x] < siz[y]) swap(x, y);

		//ｙをｘの子とする
		par[y] = x;
		siz[x] += siz[y];
		return true;
	}

	// ｘを含むグループのサイズ
	int size(int x) {
		return siz[root(x)];
	}
};
