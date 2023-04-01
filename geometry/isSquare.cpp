// 正方形判定
bool isSquare(vector<int>& x, vector<int>& y) {
	vector<int> v;
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++) {
			v.push_back((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
		}
	}
	sort(v.begin(), v.end());
	int l = v[0];
	if (l == 0) return 0; // 座標の重複判定
	return v[0] == l && v[1] == l && v[2] == l && v[3] == l && v[4] == l + l && v[5] == l + l;
}
