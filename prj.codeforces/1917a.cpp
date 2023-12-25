#include <iostream>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		int n = 0;
		std::cin >> n;
		int count = 0;
		int zero = 0;
		for (int i = 0; i < n; i += 1) {
			int a = 0;
			std::cin >> a;
			if (a == 0) {
				zero += 1;
			}
			if (a < 0) {
				count += 1;
			}
		}
		if (count % 2 != 0 || zero > 0) {
			std::cout << 0 << '\n';
		}
		else {
			std::cout << 1 << '\n' << 1 << ' ' << 0 << '\n';
		}
	}
}