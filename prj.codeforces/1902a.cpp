#include <iostream>
#include <string>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		int n = 0;
		std::cin >> n;
		std::string s;
		std::cin >> s;
		if (s.find("0") != std::string::npos) {
			std::cout << "YES" << '\n';
		}
		else {
			std::cout << "NO" << '\n';
		}
	}
}