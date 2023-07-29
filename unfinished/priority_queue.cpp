template<typename T>
ostream& operator<<(ostream& os, const priority_queue<T>& q) {
	os << "{ ";
	auto p = q;
	while (!p.empty()) {
		os << p.top() << ((int)p.size() == 1 ? "" : ", ");
		p.pop();
	}
	return os << " }";
}

template<typename T>
ostream& operator<<(ostream& os, const priority_queue<T, vector<T>, greater<T>>& q) {
	os << "{ ";
	auto p = q;
	while (!p.empty()) {
		os << p.top() << ((int)p.size() == 1 ? "" : ", ");
		p.pop();
	}
	return os << " }";
}
