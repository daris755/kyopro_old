template<typename T, typename Ta>
ostream& operator<<(ostream& os, const pair<T, Ta>& p);
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v);
template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& v);
template<typename T, size_t... index>
void printTuple(ostream& os, const T& tp, index_sequence<index...>, size_t n);
template<typename T>
void forTuple(ostream& os, const T& tp);
template<typename ...T>
ostream& operator<<(ostream& os, const tuple<T...>& tp);
template<typename T>
ostream& operator<<(ostream& os, const set<T>& s);
//ostream& operator<<(ostream& os, const __int128& x);
void print();
template<class T>
void print(const T& a);
template<class T, class... Ts>
void print(const T& a, const Ts&... b);


template<typename T, typename Ta>
ostream& operator<<(ostream& os, const pair<T, Ta>& p) {
	os << "{ " << p.first << ", " << p.second << " }";
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
	os << "[ ";
	for (size_t i = 0; i < v.size(); i++) {
		os << v[i] << (i == v.size() - 1 ? "" : ", ");
	}
	return os << " ]";
}

template<typename T>
ostream& operator<<(ostream& os, const vector<vector<T>>& v) {
	for (size_t i = 0; i < v.size(); i++) {
		os << "[ ";
		for (size_t j = 0; j < v[i].size(); j++) {
			os << v[i][j] << (j == v[i].size() - 1 ? "" : ", ");
		}
		os << " ]";
		os << (i == v.size() - 1 ? "" : "\n");
	}
	return os;
}

template<typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
	os << "{ ";
	auto itr = s.begin();
	while (itr != s.end()) {
		os << (itr == s.begin() ? "" : ", ") << *itr;
		itr++;
	}
	return os << " }";
}

template<typename T, size_t... index>
void printTuple(ostream& os, const T& tp, index_sequence<index...>, size_t n) {
	using swallow = vector<int>;
	(void)swallow
	{
		(os << get<index>(tp) << (index == n - 1 ? "" : ", "), 0)...
	};
}

template<typename T>
void forTuple(ostream& os, const T& tp) {
	constexpr size_t n = tuple_size_v<T>;
	printTuple(os, tp, make_index_sequence<n>{}, n);
}

template<typename ...T>
ostream& operator<<(ostream& os, const tuple<T...>& tp) {
	os << "{ ";
	forTuple(os, tp);
	return os << " }";
}
/*
ostream& operator<<(ostream& os, const __int128& x) {
  __int128 tmp = x;
  if (tmp == 0) return os << 0;
  if (tmp < 0) {
	os << '-';
	tmp = -tmp;
  }
  vector<int> ret;
  while (tmp) {
	ret.emplace_back(tmp % 10);
	tmp /= 10;
  }
  reverse(ret.begin(), ret.end());
  for (auto&& i : ret) os << i;
  return os;
}
*/
void print() {
	cout << '\n';
}

template<class T>
void print(const T& a) {
	cout << a << '\n';
}

template<class T, class... Ts>
void print(const T& a, const Ts&... b) {
	cout << a; (cout << ... << (cout << ' ', b));
	cout << '\n';
	//{ cout << a << ' '; print(b...); }
}
