#include <iostream>
#include <string>


int main() {
	int t = 0;
	std::cin >> t;
	char sum = char('A' + 'B' + 'C');
	for (int iTest = 0; iTest < t; iTest += 1) {
		char ans = ' ';
		for (int r = 0; r < 3; r += 1) {
			std::string s;
			std::cin >> s;
			if (s.find("?") != s.npos) {
				ans = sum + '?' - (s[0] + s[1] + s[2]);
			}
		}
		std::cout << ans << '\n';
	}
}