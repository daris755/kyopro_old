// input
// prototype
template<typename T, typename Ta> istream& operator>>(istream& is, pair<T, Ta>& p);
template<typename T> istream& operator>>(istream& is, vector<T>& v);
template<typename T> istream& operator>>(istream& is, vector<vector<T>>& v);
istream& operator>>(istream& is, __int128& x);
template<class T> void input(T& a);
template<class T, class... Ts> void input(T& a, Ts&... b);

template<typename T, typename Ta> istream& operator>>(istream& is, pair<T, Ta>& p) {
	is >> p.first >> p.second;
	return is;
}
template<typename T> istream& operator>>(istream& is, vector<T>& v) {
	for (auto&& c : v) is >> c;
	return is;
}
template<typename T> istream& operator>>(istream& is, vector<vector<T>>& v) {
	for (auto&& c : v) is >> c;
	return is;
}
istream& operator>>(istream& is, __int128& x) {
  x = 0;
  string s;
  is >> s;
  bool res = s[0] == '-';
  for (size_t i = (res ? 1 : 0); i < s.size(); i++) {
	x *= 10;
	x += s[i] - '0';
  }
  if (res) x = -x;
  return is;
}
template<class T> void input(T& a) {
	cin >> a;
}
template<class T, class... Ts> void input(T& a, Ts&... b) {
	cin >> a;
	input(b...);
}
