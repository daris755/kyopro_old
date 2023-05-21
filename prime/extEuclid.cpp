pair<ll, ll> extEuclid(const ll a, const ll b) {
	ll x = 1, y = 0, u = 0, v = 1, s = a, t = b;
	ll k;
	while (t) {
		k = s / t;
		swap(s -= k * t, t);
		swap(x -= k * u, u);
		swap(y -= k * v, v);
	}
	return make_pair(x, y);
}
