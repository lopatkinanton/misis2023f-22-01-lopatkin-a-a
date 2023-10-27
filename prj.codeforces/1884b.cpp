#include <iostream>
#include <string>

int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		int n = 0;
		std::string s;
		std::cin >> n >> s;
		long long ans = 0;
		bool f = 1;
		int p = n;
		for (int i = n - 1; i >= 0; i -= 1) {
			p--;
			while (p >= 0 && s[p] == '1') {
				p--;
			}
			if (p < 0) {
				f = 0;
			} else {
				ans += (i - p);
			}
			if (f) {
				std::cout << ans << ' ';
			}
			else {
				std::cout << -1 << ' ';
			}
		}
		std::cout << '\n';
	}
}