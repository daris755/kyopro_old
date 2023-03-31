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
