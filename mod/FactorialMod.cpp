// 階乗・組合せの逆元
class FactorialMod {
	void calc_inverse() {
		inverse[0] = 0;
		inverse[1] = 1;
		for (int i = 2; i < max_num + 1; i++) {
			inverse[i] = mod - ((mod / i) * inverse[mod % i] % mod);
		}
	}
	void calc_factorial_inverse() {
		factorial[0] = factorial_inverse[0] = 1;
		for (int i = 1; i < max_num + 1; i++) {
			factorial[i] = (factorial[i - 1] * i) % mod;
			factorial_inverse[i] = (factorial_inverse[i - 1] * inverse[i]) % mod;
		}
	}
public:
	int max_num;
	int mod;
	vector<ll> inverse;
	vector<ll> factorial; // % mod
	vector<ll> factorial_inverse;
	FactorialMod(int _max_num, const int& _mod) {
		max_num = _max_num; // n
		mod = _mod;
		inverse = vector<ll>(max_num + 1);
		factorial = vector<ll>(max_num + 1);
		factorial_inverse = vll(max_num + 1);
		calc_inverse();
		calc_factorial_inverse();
	}
	// nHk
	ll conbination_mod(int n, int k) {
		if (min(n, k) < 0 || max(n, k) > max_num || k > n) return 0;
		return (((factorial[n] * factorial_inverse[k]) % mod) * factorial_inverse[n - k]) % mod;
	}
	// nHk 重複組合せ
	ll multi_choose_mod(int n, int k) {
		return conbination_mod(n + k - 1, k);
	}
};
