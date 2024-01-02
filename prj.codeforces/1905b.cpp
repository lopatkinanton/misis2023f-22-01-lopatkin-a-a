#include <iostream>
#include <vector>


int main() {
	int t = 0;
	std::cin >> t;
	for (int iTest = 0; iTest < t; iTest += 1) {
        int n = 0;
        std::cin >> n;
        std::vector<int> vec(n + 1);
        for (int i = 0; i < n - 1; i += 1) {
            int u = 0;
            int v = 0;
            std::cin >> u >> v;
            vec[u] += 1;
            vec[v] += 1;
        }
        int count = 0;
        for (int i : vec) {
            if (i == 1) {
                count += 1;
            }
        }
        std::cout << (count + 1) / 2 << '\n';
	}
}