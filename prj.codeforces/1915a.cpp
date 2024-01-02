#include <iostream>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		int a = 0;
		int b = 0;
		int c = 0;
		std::cin >> a >> b >> c;
		int ans = a;
		if (a == b) {
			ans = c;
		}
		else if (a == c) {
			ans = b;
		} 
		std::cout << ans << '\n';
	}
}