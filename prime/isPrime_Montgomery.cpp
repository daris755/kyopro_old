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
        // https://math-koshimizu.hatenablog.jp/entry/2016/12/15/000000
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

// https://drken1215.hatenablog.com/entry/2023/05/23/233000
bool MillerRabin(ll n, vector<ll> A) {
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

bool isPrime(ll n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    if (n < 4759123141LL) return MillerRabin(n, {2, 7, 61});
    else return MillerRabin(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}
