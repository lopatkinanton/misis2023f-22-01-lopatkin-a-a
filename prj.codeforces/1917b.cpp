#include <iostream>
#include <string>
#include <set>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		int n = 0;
		std::cin >> n;
		std::string s;
		std::cin >> s;
		std::set<char> cnt;
		long long ans = 0;
		for (int i = 0; i < n; i += 1) {
			cnt.insert(s[i]);
			ans += cnt.size();
		}
		std::cout << ans << '\n';
	}
}