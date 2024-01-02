#include <iostream>
#include <algorithm>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		int n = 0;
		int m = 0;
		std::cin >> n >> m;
		std::cout << std::max(n, m) << '\n';
	}
}