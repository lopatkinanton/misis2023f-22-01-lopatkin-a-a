#include <iostream>
#include <string>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		std::string s;
		std::cin >> s;
		int ans = 0;
		int zeros = 0;
		int ones = 0;
		for (int i = 0; i < s.length(); i += 1) {
			if (s[i] == '0') {
				zeros += 1;
			}
			else {
				ones += 1;
			}
		}
		for (int i = 0; i < s.length(); i += 1) {
			if (s[i] == '0') {
				ones -= 1;
			}
			else {
				zeros -= 1;
			}
			if (zeros < 0 || ones < 0) {
				ans += 1;
			}
		}
		std::cout << ans << '\n';
	}
}