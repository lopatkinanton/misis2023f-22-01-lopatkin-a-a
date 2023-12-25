#include <iostream>
#include <string>
#include <vector>


int main() {
	int queries = 0;
	std::cin >> queries;
	std::vector<int> vec(31);
	for (int iQuery = 0; iQuery < queries; iQuery += 1) {
		int type = 0;
		int x = 0;
		std::cin >> type >> x;
		if (type == 1) {
			vec[x] += 1;
		}
		else if (type == 2) {
			std::string ans = "YES";
			std::vector<int> tmp = vec;
			for (int i = 0; i < 30; i += 1) {
				if (((x >> i) & 1)) {
					if (tmp[i] > 0) {
						tmp[i] -= 1;
					}
					else {
						ans = "NO";
						break;
					}
				}
				tmp[i + 1] += tmp[i] / 2;
			}
			std::cout << ans << '\n';
		}
	}
}