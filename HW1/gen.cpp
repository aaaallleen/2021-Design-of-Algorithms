#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

int cases = 0;

void open_file() {
    char str[128];
    sprintf(str, "TestCases/%02d.in", ++cases);
    if (freopen(str, "w", stdout) == NULL) {
		cerr << "Unable to write file " << str << '\n';
		exit(0);
	} 
}

const int n = 20000000;
const int mod = 10000000;

inline int get_rand() {
	return (1LL * (rand() % mod) * (rand() % mod) % mod + rand()) % mod + 1;
}
void gen(int group_size) {
	open_file();
	cout << n << ' ' << (rand() % n + 1) << ' ' << group_size << '\n';
	for (int i = 0; i < n; i++) {
		cout << get_rand() << " \n"[i == n - 1];
	}
}

int main(int argc, char** argv) {
	srand(time(NULL));
	for (int group_size : {-1, 3, 5, 7, 9}) {
		for (int i = 0; i < 5; i++) {
			gen(group_size);
		}
	}
	return 0;
}

