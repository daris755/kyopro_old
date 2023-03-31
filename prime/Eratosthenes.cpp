struct Eratosthenes {
	// 素数テーブル
	vector<bool> isprime;
	// 整数ｉを割り切る最小の素数
	vector<int> minfactor;

	Eratosthenes(int n) : isprime(n + 1, 1), minfactor(n + 1, -1) {
		isprime[1] = 0;
		minfactor[1] = 1;
		for (int p = 2; p <= n; p++) {
			if (!isprime[p]) continue;
			minfactor[p] = p;
			for (int q = p * 2; q <= n; q += p) {
				isprime[q] = 0;
				if (minfactor[q] == -1) minfactor[q] = p;
			}
		}
	}

	// 高速素因数分解
	vector<pair<int, int>> factorize(int n) {
		vector<pair<int, int>> res;
		while (n > 1) {
			int p = minfactor[n];
			int exp = 0;
			while (minfactor[n] == p) {
				n /= p;
				exp++;
			}
			res.emplace_back(p, exp);
		}
		return res;
	}

	// 高速約数列挙
	vector<int> divisors(int n) {
		vector<int> res({ 1 });
		const auto& pf = factorize(n);
		for (auto [p, q] : pf) {
			int rsz = res.size();
			for (int i = 0; i < rsz; i++) {
				int v = 1;
				for (int j = 0; j < q; j++) {
					v *= p;
					res.emplace_back(res[i] * v);
				}
			}
		}
		return res;
	}
};
