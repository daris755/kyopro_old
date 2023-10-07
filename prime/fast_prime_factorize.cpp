// verify -> https://judge.yosupo.jp/submission/164945

// https://yukicoder.me/wiki/モンゴメリ乗算
struct MontgomeryModInt64 {
    using mint = MontgomeryModInt64;
    using u64 = uint64_t;
    using u128 = __uint128_t;
    
    static u64 mod;  // m
    static u64 inv;  // m_inverse
    static u64 r;  // 2^128 (mod m)
    
    u64 x;
    
    // constructor
    MontgomeryModInt64(ll a = 0) : x(reduce((u128(a) + mod) * r)) { }
    u64 get() const {
        u64 t = reduce(x);
        return t >= mod ? t - mod : t;
    }
    
    // mod & inv initialize(get)
    static u64 get_mod() { return mod; }
    static void set_mod(u64 m) {
        assert(m < (1ll << 62));
        assert((m & 1));
        mod = m;
        inv = get_inv();
        r = -u128(m) % m;  // wrap around
    }
    
    static u64 get_inv() {
        // ニュートン法
        // https://qiita.com/hotman78/items/f0e6d2265badd84d429a
        u64 xn = mod;
        for (int i = 0; i < 5; i++) xn = xn * (2 - mod * xn);
        return xn;
    }
    
    static u64 reduce(const u128& a) {
        return (a + u128(u64(a) * u64(-inv)) * mod) >> 64;
    }
    
    // operators
    mint& operator+=(const mint &r) {
        if ((x += r.x) >= 2 * mod) x -= 2 * mod;
        return *this;
    }
    mint& operator-=(const mint &r) {
        if ((x += 2 * mod - r.x) >= 2 * mod) x -= 2 * mod;
        return *this;
    }
    mint& operator*=(const mint &r) {
        x = reduce(u128(x) * r.x);
        return *this;
    }
    mint& operator/=(const mint &r) {
        *this *= r.inverse();
        return *this;
    }
    
    mint operator-() const { return mint() - mint(*this); }
    mint operator+(const mint& r) const { return mint(*this) += r; }
    mint operator-(const mint& r) const { return mint(*this) -= r; }
    mint operator*(const mint& r) const { return mint(*this) *= r; }
    mint operator/(const mint& r) const { return mint(*this) /= r; }
    bool operator==(const mint& r) { return (x >= mod ? x - mod : x) == (r.x >= mod ? r.x - mod : r.x); }
	bool operator!=(const mint& r) { return (x >= mod ? x - mod : x) != (r.x >= mod ? r.x - mod : r.x); }
    
    mint inverse() const { return power(mod - 2); }

	mint power(u128 k) const {
	    mint res = 1, y = x;
		while (k) {
			if (k & 1) res *= y;
			y *= y;
			k >>= 1;
		}
		return res;
	}

	friend istream& operator>>(istream& is, mint& r) {
		ll s;
		is >> s;
		r = mint(s);
		return is;
	}

	friend ostream& operator<<(ostream& os, const mint& r) {
		return os << r.get();
	}
};

// typename
// MontgomeryModInt64はu64という型であることを示す文法
// https://daily-tech.hatenablog.com/entry/2018/12/01/103658

// static
// 構造体からアクセスできるグローバル変数と思う？
// http://vivi.dyndns.org/tech/cpp/static.html#member_var
typename MontgomeryModInt64::u64
MontgomeryModInt64::mod, MontgomeryModInt64::inv, MontgomeryModInt64::r;

// kをテストの回数として O(klogn)
// https://drken1215.hatenablog.com/entry/2023/05/23/233000
bool miller_rabin(ll n, vector<ll> A) {
    using mint = MontgomeryModInt64;
    mint::set_mod(n);
    
    ll s = 0, d = n - 1;
    while (d % 2 == 0) {
        s++;
        d >>= 1;
    }
    for (auto&& a : A) {
        // 例えば15は a = 2 で落とせる
        if (n <= a) return true;
        ll t;
        mint x = mint(a).power(d);
        if (x != 1) {
            for (t = 0; t < s; t++) {
                // n - 1 ≡ -1 (mod n)
                // このとき n は素数かもしれない
                if (x == n - 1) break;
                x *= x;
            }
            // すべて成り立たないならば n は素数でない
            if (t == s) return false;
        }
    }
    // すべての a が n のテストに通ったら n は素数
    return true;
}

bool is_prime(ll n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    if (n < 4759123141LL) return miller_rabin(n, {2, 7, 61});
    else return miller_rabin(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

// ポラードのロー法
// https://qiita.com/t_fuki/items/7cd50de54d3c5d063b4a#%E3%83%96%E3%83%AC%E3%83%B3%E3%83%88%E3%81%AE%E5%BE%AA%E7%92%B0%E6%A4%9C%E5%87%BA%E6%B3%95
template<typename T>
T pollard_rho(T n) {
    if (~n & 1) return 2;
    if (is_prime(n)) return n;
    using mint = MontgomeryModInt64;
    mint::set_mod(n);
    mint c;
    auto f = [&](mint x) { return (x * x + c); };
    int m = int(pow(n, 0.125)) + 1;
    for (c = 1; ; c += 1) {
        mint x = 0, y = 0, ys, q = 1;
        T g = 1, k = 0, r = 1;
        while (g == 1) {
            x = y;
            while (k < 3 * r / 4) {
                y = f(y);
                k++;
            }
            while (k < r && g == 1) {
                ys = y; // バックトラック用の変数
                for (int i = 0; i < m && i < r - k; i++) {
                    y = f(y);
                    q *= x - y;
                }
                g = gcd(q.get(), n);
                k += m;
            }
            k = r;
            r *= 2;
        }
        if (g == n) {
            do {
                ys = f(ys);
                g = gcd((x - ys).get(), n);
            } while (g == 1);
        }
        if (g != n) return g;
    }
}

// O(n^(1/4))
vector<ll> inner_prime_factorize(ll n) {
    if (n <= 1) return {};
    ll p = pollard_rho(n);
    if (p == n) return {p};
    auto l = inner_prime_factorize(p);
    auto r = inner_prime_factorize(n / p);
    copy(r.begin(), r.end(), back_inserter(l));
    return l;
}

vector<ll> prime_factorize(ll n) {
    auto ret = inner_prime_factorize(n);
    sort(ret.begin(), ret.end());
    return ret;
}

map<ll, ll> prime_factor_count(ll n) {
    map<ll, ll> mp;
    for (auto&& x : prime_factorize(n)) mp[x]++;
    return mp;
}

vector<ll> divisors(ll n) {
    if (n == 0) return {};
    vector<pair<ll, ll>> v;
    for (auto&& p : prime_factorize(n)) {
        if (v.empty() || v.back().first != p) {
             v.emplace_back(p, 1);
        }
        else v.back().second++;
    }
    vector<ll> ret = {1};
    for (auto&& [p, e] : v) {
        int sz = (int)ret.size();
        for (int i = 0; i < sz; i++) {
            ll x = 1;
            for (int j = 0; j < e; j++) {
                x *= p;
                ret.emplace_back(ret[i] * x);
            }
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}
