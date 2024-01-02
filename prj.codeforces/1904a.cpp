#include <iostream>
#include <vector>
#include <set>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
		int a = 0;
		int b = 0;
		std::cin >> a >> b;
		int xk = 0;
		int yk = 0;
		std::cin >> xk >> yk;
		int xq = 0;
		int yq = 0;
		std::cin >> xq >> yq;
		int ans = 0;
		std::vector<std::pair<int, int>> d = { {a, b}, {a, -b}, {-a, b}, {-a, -b}, {b, a}, {b, -a}, {-b, a}, {-b, -a} };
		std::set<std::pair<int, int>> s1, s2;
		for (auto i : d) {
			s1.insert({ xk + i.first, yk + i.second });
			s2.insert({ xq + i.first, yq + i.second });
		}
		for (auto i : s1) {
			if (s2.find(i) != s2.end()) {
				ans += 1;
			}
		}
		std::cout << ans << '\n';
	}
}