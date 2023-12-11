#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int n, k, g; cin >> n >> k >> g;	
	vector<int> v(n);
	for (int& i : v) cin >> i;
	nth_element(v.begin(), v.begin() + k - 1, v.end());
	cout << v[k - 1] << '\n';
	return 0;
}

