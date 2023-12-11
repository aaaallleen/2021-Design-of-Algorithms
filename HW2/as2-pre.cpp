#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
int n;
int mp[31][31];
class Node{
    public:
    vector<int> path;
    int bound;
    int cost;
	Node (vector<int> _path, int _nxt, int _bound, int _cost) : path(_path), bound(_bound), cost(_cost) {
		path.push_back(_nxt);
	}
	Node() = default;
};
class Compare{
    public:
    bool operator()(const Node& a, const Node& b){
        return (a.bound == b.bound)?(a.path.size() < b.path.size()):a.bound>b.bound;
    }
};
uint32_t get_able(vector<int>& v) {
	uint32_t able = (1u << 31) - 1;
	for (auto it : v) {
		able ^= (1u << (it - 1));
    }
	return able;
}
int calcbound(uint32_t able, int lst){
	able |= (1u << (lst - 1));
    int bound = 0;
    for(int i = 0; i<n; i++){
		int mn = 10000000;
		if (!(able & (1u << i))) continue;
        for(int j = 0; j<n; j++){
            if((!(able&(1u << j)) || j == lst-1) &&j!=1 && lst != 1){}
            else if(mp[i][j] < mn && i != j)mn = mp[i][j];
        }
        if(mn != 10000000){
            bound += mn;
        }
    }
    return bound;
}
int optimal_c = 1000000000;
vector<int> optiaml_p;
priority_queue<Node, vector<Node>, Compare> PQ;
int main(){
    cin>>n;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cin>>mp[i][j];
        }
    }
    Node u(vector<int>(0), 1, calcbound((1u << 31) - 1, 1), 0);
    PQ.emplace(u);
    Node nv;
    while(!PQ.empty()){
        Node v = PQ.top(); PQ.pop();                                                               
        if(v.bound >= optimal_c)break;
		uint32_t able = get_able(v.path);
        for(int i = 1; i<n; i++){                                               
            if(!(able & (1 << i)) || mp[v.path.back()-1][i]==0) continue;                       
            nv.cost = v.cost + mp[v.path.back()-1][i];
            nv.path = v.path;
            nv.path.push_back(i+1);                                             
            if((int) nv.path.size()==n-1){
                int last;
                for(int k = 1; k<n; k++){
                    if(k==i)continue;
					if (able & (1 << k)) last = k;
                }
                nv.path.push_back(last+1);
                nv.cost+=mp[i][last]; 
                nv.cost+=mp[last][0];                                      
                if(nv.cost<optimal_c){
                    optimal_c = nv.cost;
                    optiaml_p = nv.path;
                }
                continue;
            }
            else{
                nv.bound = calcbound(get_able(nv.path), nv.path.back())+nv.cost;
                if(nv.bound > optimal_c){
                    continue;
                }
                PQ.emplace(nv);
            }
        }
    }
    cout << optimal_c << '\n';
    for(auto it : optiaml_p){
        cout << it << " ";
    }
    cout << '\n';
    
    return 0;
}
