#include <iostream>
#include <string>
#include <vector>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		int n = 0;
		std::cin >> n;
		std::string s;
		std::cin >> s;
		std::vector<char> cv(n + 2, 'c');
		cv[n + 1] = 'v';
		for (int i = 0; i < n; i += 1) {
			if (s[i] == 'a' || s[i] == 'e') {
				cv[i] = 'v';
			}
		}
		int p = 0;
		std::string ans;
		for (int i = 1; i < n; i += 1) {
			if (cv[i] == 'v' && cv[i+1] == 'c' && cv[i + 2] == 'v') {
				ans += (s.substr(p, 2) + ".");
				p = i + 1;
			}
			if (cv[i] == 'c' && cv[i + 1] == 'c') {
				ans += (s.substr(p, 3) + ".");
				p = i + 1;
			}
		}
		ans.pop_back();
		std::cout << ans << '\n';
	}
}