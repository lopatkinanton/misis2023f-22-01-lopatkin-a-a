#include <iostream>
#include <cmath>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		int n = 0;
		std::cin >> n;
		long long sum = 0;
		for (int i = 0; i < n; i += 1) {
			long long a = 0;
			std::cin >> a;
			sum += a;
		}
		long long sqrt = std::sqrt(sum);
		if (sqrt * sqrt == sum) {
			std::cout << "YES" << '\n';
		}
		else {
			std::cout << "NO" << '\n';
		}
	}
}