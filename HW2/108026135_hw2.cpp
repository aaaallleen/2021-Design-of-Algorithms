#include <iostream> 
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
using namespace std;

const int N = 16;
const int INF = (1 << 29);
int n, ub = INF; 
int w[N][N], maskr[N], maskc[N];
//int cpy[N][N];
struct P { int x, y; };
vector<P> ans, tmp;
ifstream fin;
ofstream fout;
clock_t a, b;

int Reduce() {
	int lb = 0;
	for (int i = 0; i < n; i++) {
		if (maskr[i]) continue;
		int mn = INF;
		for (int j = 0; j < n; j++) if (!maskc[j]) mn = min(mn, w[i][j]);
		if (mn == INF) continue;
		for (int j = 0; j < n; j++) if (!maskc[j] && w[i][j] != INF) w[i][j] -= mn;
		lb += mn;
	}
	for (int i = 0; i < n; i++) {
		if (maskc[i]) continue;
		int mn = INF;
		for (int j = 0; j < n; j++) if (!maskr[j]) mn = min(mn, w[j][i]);
		if (mn == INF) continue;
		for (int j = 0; j < n; j++) if (!maskr[j] && w[j][i] != INF) w[j][i] -= mn;
		lb += mn;
	}
	return lb;
}
P select() {
	P res = {-1, -1};
	int mn = -1;
	for (int i = 0; i < n; i++) {
		if (maskr[i]) continue;
		for (int j = 0; j < n; j++) {
			if (maskc[j]) continue;
			int tmpr = INF, tmpc = INF;
			for (int k = 0; k < n; k++) {
				if (!maskc[k] && i != k && k != j) tmpr = min(tmpr, w[i][k]);
				if (!maskr[k] && k != j && k != i) tmpc = min(tmpc, w[k][j]);
			}	
			if (tmpr + tmpc > mn) res = {i, j}, mn = tmpr + tmpc;
		}
	}
	return res;
}
int** copy() {
	int** cpy = new int*[n];
	for (int i = 0; i < n; i++) {
		cpy[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cpy[i][j] = w[i][j];
		}
	}
	return cpy;
}
void del(int** cpy) {
	for (int i = 0; i < n; i++) delete[] cpy[i];
	delete[] cpy;
}
void assign(int **cpy) {
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			w[i][j] = cpy[i][j];
}
int check() {
	vector<int> to(n, 0);
	for (size_t i = 0; i < tmp.size(); i++) {
		to[tmp[i].x] = tmp[i].y;
	}
	int now = to[0], cnt = 1;
	while (now != 0) {
		cnt++;
		now = to[now];
	}
	return cnt == n;
}
void BB_TSP(int lb, int cnt) {
	int** cpy = copy();
	int newlb = lb + Reduce();
	if (lb >= ub) return del(cpy);
	if (cnt == n) {
		if (!check()) return;
		ans = tmp;
		ub = lb;
		return del(cpy);
	}
	auto wh = select();
	if (wh.x == -1 || w[wh.x][wh.y] >= INF) return del(cpy);

	newlb += w[wh.x][wh.y];
	maskr[wh.x] = maskc[wh.y] = 1;
	w[wh.y][wh.x] = INF;
	tmp.emplace_back(wh);
	BB_TSP(newlb, cnt + 1);

	assign(cpy);
	tmp.pop_back();
	w[wh.x][wh.y] = INF;
	maskr[wh.x] = maskc[wh.y] = 0;
	BB_TSP(lb, cnt);

	assign(cpy);
	del(cpy);
}
int main() { 
	fin.open("tsp_input.txt");
	fout.open("BB.txt");
	while(fin >> n){
		a = clock();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				fin >> w[i][j];
				if (i == j) w[i][j] = INF;
			}
		}
		ub = INF;
		fill(maskr, maskr + N, 0);
		fill(maskc, maskc + N, 0);
		tmp.clear();
		ans.clear();
		BB_TSP(0, 0);
		b = clock();
		vector<int> to(n);
		for (size_t i = 0; i < ans.size(); i++) to[ans[i].x] = ans[i].y; 
		int now = to[0];
		fout << "Solution : " << 0;
		do {
			fout << " - " << now;
			now = to[now];
		} while(now != 0);
		fout << " - " << 0 << endl;
		fout << "Cost : " << ub << endl;
		fout << "Time : " << fixed << setprecision(12) << double(b - a) / CLOCKS_PER_SEC << " s" << endl;
		fout << endl;
	}
	return 0;
}