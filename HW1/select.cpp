#include <iostream>
#include <vector>

using namespace std;

int randomize_partition(vector<int>& arr, int l, int r) {
	int x = arr[r];
	int i = l;
	for (int j = l; j < r; j++) {
		if (arr[j] <= x) {
			swap(arr[i], arr[j]);
			i += 1;
		}
	}
	swap(arr[i], arr[r]);
	return i;
}

// k: 0-based
int randomize_select(vector<int>& arr, int l, int r, int k) {
	if (l == r) return arr[l]; 
	int m = randomize_partition(arr, l, r);
	if (m - l == k) return arr[m];
	if (m - l > k) return randomize_select(arr, l, m - 1, k);
	return randomize_select(arr, m + 1, r, k - (m - l + 1));
}


inline void sort_sub_vector(vector<int>& arr, int l, int r) {
	for (int i = l + 1; i < r; i++) {
		int id = i, key = arr[i];
		while (id >= l + 1 && arr[id - 1] > key) {
			arr[id] = arr[id - 1];
			id--;
		}
		arr[id] = key;
	}
}
int select(vector<int>& arr, int k, int group_size) {
	if ((int) arr.size() < group_size) {
		sort_sub_vector(arr, 0, arr.size());
		return arr[k];
	}
	int n = arr.size();
	int m;
	{
		vector<int> median;
		for (int i = 0; i < n; i += group_size) {
			if (i + group_size <= n) {
				sort_sub_vector(arr, i, i + group_size);
				median.push_back(arr[i + group_size / 2]);
			} 
			// ignore the fewer item group, it won't effect the time complexity
		}
		m = select(median, median.size() / 2, group_size);
	}
	vector<int> X, Y;
	for (int it : arr) {
		if (it < m) X.push_back(it);
		else if (it > m) Y.push_back(it);
	}
	int m_size = n - X.size() - Y.size();
	if (k < (int) X.size()) return select(X, k, group_size);
	else if (k < (int) X.size() + m_size) return m; 
	else return select(Y, k - (X.size() + m_size), group_size);
}

int main() {
	int n, k, group_size; cin >> n >> k >> group_size;
	vector<int> arr(n);
	for (int& it : arr) cin >> it;
	if (group_size == -1) {
		cout << randomize_select(arr, 0, n - 1, k - 1) << '\n';
	} else {
		cout << select(arr, k - 1, group_size) << '\n';
	}
	return 0;
}

