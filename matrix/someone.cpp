// 行列乗算
vector<vector<ll>> multiplication(vector<vector<ll>> A, vector<vector<ll>> B) {
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
vector<vector<ll>> power(vector<vector<ll>> A, ll k) {
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
