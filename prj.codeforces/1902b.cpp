#include <iostream>
#include <algorithm>


int main() {
	int tc = 0;
	std::cin >> tc;
	for (int iTest = 0; iTest < tc; iTest += 1) {
		long long n = 0;
		long long p = 0;
		long long l = 0;
		long long t = 0;
		std::cin >> n >> p >> l >> t;
		long long lp = 0;
		long long rp = n;
		while (lp + 1 < rp) {
			long long mid = (lp + rp) / 2;
			if (mid * l + std::min(mid * 2, (n + 6) / 7) * t >= p) {
				rp = mid;
			}
			else {
				lp = mid;
			}
		}
		std::cout << n - rp << '\n';
	}
}