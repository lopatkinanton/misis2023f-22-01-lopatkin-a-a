#include <iostream>
#include <string>
#include <cmath>


int strToNum(std::string s) {
	int num = 0;
	int p = s.length() - 1;
	for (int i = 0; i < s.length(); i += 1) {
		num += int(s[i] - '0') * std::pow(10, p - i);
	}
	return num;
}


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		std::string s;
		std::cin >> s;
		int a = 0;
		int b = 0;
		int ans = 0;
		for (int i = 1; i * 2 <= s.length(); i += 1) {
			if (s[i] != '0') {
				a = strToNum(s.substr(0, i));
				b = strToNum(s.substr(i, s.length() - i));
				if (a < b) {
					ans = 1;
					break;
				}
			}
		}
		if (ans) {
			std::cout << a << ' ' << b << '\n';
		}
		else {
			std::cout << -1 << '\n';
		}
	}
}