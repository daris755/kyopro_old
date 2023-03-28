bool isPrime(ll n) {
	if (n == 1) return 0;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i == 0) return 0;
	}
	return 1;
}

vector<ll> enumDivisors(ll n) {
	vector<ll> res;
	for (ll i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			res.push_back(i);
			if (n / i != i) res.push_back(n / i);
		}
	}
	sort(all(res));
	return res;
}

vector<pair<ll, ll>> primeFactorize(ll n) {
	vector<pair<ll, ll>> res;
	for (ll i = 2; i * i <= n; i++) {
		if (n % i != 0) continue;
		ll ex = 0;
		while (n % i == 0) {
			ex++;
			n /= i;
		}
		res.push_back({ i, ex });
	}
	if (n != 1) res.push_back({ n, 1 });
	return res;
}

vector<bool> Eratosthenes(size_t n) {
	vector<bool> res(n + 1, 1);
	res[0] = res[1] = 0;
	for (size_t i = 2; i < n + 1; i++) {
		if (!res[i]) continue;
		for (size_t j = 2 * i; j <= n; j += i) res[j] = 0;
	}
	return res;
}









//正方形判定
bool isSquare(vector<int>& x, vector<int>& y) {
	vector<int> v;
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			v.push_back((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
		}
	}
	sort(all(v));
	int l = v[0];
	if (l == 0) return 0; //座標の重複判定
	return v[0] == l && v[1] == l && v[2] == l && v[3] == l && v[4] == l + l && v[5] == l + l;
}

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

void charm() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15);
}


// 行列乗算
vector<vector<ll>> matrixMultiplication(vector<vector<ll>> A, vector<vector<ll>> B) {
	// A : (l, n)型行列, B : (n, m)型行列
	int l = A.size();
	int m = B[0].size();
	int n = B.size(); // == A[0].size();
	// AB : (l, m)行列
	vector<vector<ll>> AB(l, vector<ll>(m));
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < n; k++) {
				AB[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return AB;
}

// 行列累乗
vector<vector<ll>> matrixPower(vector<vector<ll>> A, ll k) {
	int n = A.size();
	vector<vector<ll>> res(n, vector<ll>(n));
	for (int i = 0; i < n; i++) res[i][i] = 1;
	while (k) {
		if (k & 1) res = matrixMultiplication(res, A);
		A = matrixMultiplication(A, A);
		k >>= 1;
	}
	return res;
}



// 行列乗算mod
vector<vector<ll>> matrixMultiplicationMod(vector<vector<ll>> A, vector<vector<ll>> B, ll mod) {
	// A : (l, n)型行列, B : (n, m)型行列
	int l = A.size();
	int m = B[0].size();
	int n = B.size(); // == A[0].size();
	// AB : (l, m)行列
	vector<vector<ll>> AB(l, vector<ll>(m));
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < n; k++) {
				AB[i][j] += A[i][k] * B[k][j];
				AB[i][j] %= mod;
			}
		}
	}
	return AB;
}

// 行列累乗mod
vector<vector<ll>> matrixPowerMod(vector<vector<ll>> A, ll k, ll mod) {
	int n = A.size();
	vector<vector<ll>> res(n, vector<ll>(n));
	for (int i = 0; i < n; i++) res[i][i] = 1;
	while (k) {
		if (k & 1) res = matrixMultiplicationMod(res, A, mod);
		A = matrixMultiplicationMod(A, A, mod);
		k >>= 1;
	}
	return res;
}
