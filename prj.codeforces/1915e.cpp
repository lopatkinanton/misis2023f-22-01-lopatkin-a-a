#include <iostream>
#include <set>
#include <vector>
#include <string>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		long long n = 0;
		std::cin >> n;
		std::vector<long long> a(n);
		std::vector<long long> p(n + 1, 0);
		std::string ans = "NO";
		std::set<long long> st;
		st.insert(0);
		for (int i = 0; i < n; i += 1) {
			std::cin >> a[i];
			p[i + 1] = p[i] + (i % 2 == 0 ? a[i] : -a[i]);
			if (st.find(p[i + 1]) != st.end()) {
				ans = "YES";
			}
			st.insert(p[i + 1]);
		}
		std::cout << ans << '\n';
	}
}