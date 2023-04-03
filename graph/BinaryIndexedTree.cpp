template<typename T>
struct BinaryIndexedTree {
	// https://scrapbox.io/pocala-kyopro/BIT

	int n;
	vector<T> bit;

	BinaryIndexedTree(int n) : n(n), bit(n + 1) {}

	// 一点更新
	void add(int k, T v) {
		// i & -i で立っている最下位ビットを取りだす
		for (int i = k; i <= n; i += i & -i) bit[i] += v;
	}

	// １～ｎまでの和を求める
	ll sum(int k) {
		ll res = 0;
		for (int i = k; 0 < i; i -= i & -i) res += bit[i];
		return res;
	}

};

template<class T> using BIT = BinaryIndexedTree<T>;
