#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
#include <queue>
#include <ctime>
using namespace std;
int N;
int INF = 2147483647;
int w[30][30];
vector<int> path;
clock_t a, b;
struct node{
    int cost;
    int level;
    int bound;
    int label;
    vector<int> path;
};

struct cmp{
    public:
    bool operator()(const node x,const node y){
        return (x.bound == y.bound)?(x.level < y.level):(x.bound > y.bound);
    }
};
int genlen(node n){
    int sum = 0;
    for (int i = 1; i < n.path.size(); i++){
        sum += w[n.path[i]][n.path[i-1]];
    }
    return sum;
}
// int calcbound(node n){
//     int min;
//     int lb = 0;
//     for(int i = 0 ; i < N; i++){
//         min = INF;
//         if(visited[i]!= -1) continue;
//         for(int j = 0; j < N ; j++){
//             if((visited[j]!= -1 || j == n.label-1) && j!= 1 && n.label!= 1) continue;
//             else if(w[i][j]< min) min = w[i][j];
//         }
//         if(min!= INF)
//             lb += min;
//     }
//     return lb;
// }
int calcbound(node nd){
    int able[31];
    for(int i = 0; i<31; i++)able[i]=1;
    vector<int>::iterator end = nd.path.end();
    for(vector<int>::iterator it = nd.path.begin(); it != end; ++it){
        able[*it-1] = 0;
    }
    able[nd.label-1] = 1;
    int min = 10000000;
    int bound = 0;
    for(int i = 0; i<N; i++){
        if(able[i]==0)continue;
        for(int j = 0; j<N; j++){
            if((able[j]==0 || j ==nd.label-1) &&j!=1 && nd.label != 1){}
            else if(w[i][j]<min)min = w[i][j];
        }
        if(min!=10000000){
            bound += min;
        }
        min = 10000000;
    }
    return bound;
}
int main(){
    cin >> N;
    int optimalsol = INF;
    
    
    priority_queue<node, vector<node>, cmp> PQ;
    for(int i = 0; i< N; i++){
        for(int j = 0; j < N; j++){
            cin >> w[i][j];
            if(i == j) w[i][j] = INF;
        }
    }
    path.reserve(N+1);
    a = clock();
    node u;
    u.path = {1};
    u.cost = 0;
    u.level = 1;
    u.label = 1;
    u.bound = calcbound(u);
    cout << u.bound;
    PQ.push(u);
    // cout << tmplb;
    node v;
    while(!PQ.empty()){
        vector<int> visited(N);
        fill(visited.begin(), visited.end(), -1);
        v = PQ.top();
        PQ.pop();
        if(v.bound > optimalsol) break;
        visited[v.label] = v.level;
        for(int i = 1; i <N; i++){
            if(visited[i] != -1 || w[v.label-1][i] == INF) continue;
            node nv;
            nv.level = v.level+1;
            nv.cost = v.cost + w[v.label-1][i];
            nv.label = i+1;
            nv.path = v.path;
            nv.path.push_back(i+1);
            visited[i+1] = nv.level;
            if(nv.level==N-1){
                int last;
                for(int k = 1; k<N; k++){
                    if(k==i)continue;
                    if(visited[k]==-1)last = k;
                }
                nv.path.push_back(last+1);
                nv.cost+=w[nv.label-1][last]; 
                nv.cost+=w[last][0];                                      //go back to 1
                if(nv.cost<optimalsol){
                    optimalsol = nv.cost;
                    path = nv.path;
                }
                continue;
            }
            else{
                nv.bound = calcbound(nv)+nv.cost;
                if(nv.bound > optimalsol){
                    continue;
                }
                PQ.push(nv);
            }
        }
    }


    cout << optimalsol << endl;
    vector<int>::iterator end = path.end();
    for(vector<int>::iterator it = path.begin(); it != end; ++it){
        cout << *it << " ";
    }
    cout << endl;

    b = clock();
    cout << "Time : " << fixed << setprecision(12) << double (b-a)/CLOCKS_PER_SEC << " seconds.\n";
}
