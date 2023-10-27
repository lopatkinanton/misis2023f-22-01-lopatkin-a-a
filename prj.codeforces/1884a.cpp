#include <iostream>

int SumDigits(int n) {
	int sum = 0;
	while (n > 0) {
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		int x = 0;
		int k = 0;
		std::cin >> x >> k;
		while (SumDigits(x) % k != 0) {
			x += 1;
		}
		std::cout << x << '\n';
	}
}