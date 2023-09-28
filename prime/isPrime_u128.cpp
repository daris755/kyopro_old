bool MillerRabin(ll n, vector<ll> A) {
    ll s = 0, d = n - 1;
    while (d % 2 == 0) {
        s++;
        d >>= 1;
    }
    for (auto&& a : A) {
        // 例えば15は a = 2 で落とせる
        if (n <= a) return true;
        ll t, x = powerMod<__int128_t>(a, d, n);
        if (x != 1) {
            for (t = 0; t < s; t++) {
                // n - 1 ≡ -1 (mod n)
                // このとき n は素数かもしれない
                if (x == n - 1) break;
                x = __int128_t(x) * x % n;
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
