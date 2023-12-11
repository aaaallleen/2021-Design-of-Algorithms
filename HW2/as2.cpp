#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;
int n;
int map[31][31];
class Node{
    public:
    vector<int> path;
    int level;
    int bound;
    int cost;
    int now;
    ~Node(){
        //delete &map;
    }
    Node(){
        level = 0;
        bound = 0;
        cost = 0;
    }
};
class Compare{
    public:
    bool operator()(Node a, Node b){
        return (a.bound == b.bound)?(a.level < b.level):a.bound>b.bound;
    }
};
int calcbound(Node nd){
    int able[31];
    for(int i = 0; i<31; i++)able[i]=1;
    vector<int>::iterator end = nd.path.end();
    for(vector<int>::iterator it = nd.path.begin(); it != end; ++it){
        able[*it-1] = 0;
    }
    able[nd.now-1] = 1;
    int min = 10000000;
    int bound = 0;
    for(int i = 0; i<n; i++){
        if(able[i]==0)continue;
        for(int j = 0; j<n; j++){
            if((able[j]==0 || j ==nd.now-1) &&j!=1 && nd.now != 1){}
            else if(map[i][j]<min && map[i][j]!=0)min = map[i][j];
        }
        if(min!=10000000){
            bound += min;
        }
        min = 10000000;
    }
    return bound;
}
int main(){
    int optimal_c = 1000000000;
    int able[31];
    vector<int> optiaml_p;
    priority_queue<Node, vector<Node>, Compare> PQ;
    for(int i = 0; i<31; i++){
        for(int j = 0; j<31; j++){
            map[i][j] = 0;
        }
    }
    cin>>n;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            cin>>map[i][j];
        }
    }
	int star_time = GetTickCount();
    Node u;
    u.path.push_back(1);
    u.cost = 0;
    u.level = 1;
    u.now = 1;
    u.bound = calcbound(u);
    PQ.push(u);
    int tmp = u.bound;
    cout << u.bound;
    // Node v,nv;
    // while(!PQ.empty()){
    //     v = PQ.top();
    //     PQ.pop();                                                               //best first search
    //     if(v.bound>optimal_c)break;
    //     for(int j = 1; j<31; j++)able[j]=1;
    //     vector<int>::iterator end = v.path.end();
    //     for(vector<int>::iterator it = v.path.begin(); it != end; ++it){
    //         able[*it-1] = 0;
    //     }                                                                       //able -> which city have been visited
    //     able[0] = 0;
    //     for(int i = 1; i<n; i++){                                               //from 1 because we cant go back to 1 before end
    //         if(able[i]==0 || map[v.now-1][i]==0)continue;                       //If the city have been visited or there's no edge
    //         nv.level = v.level+1;
    //         nv.cost = v.cost + map[v.now-1][i];
    //         nv.path = v.path;
    //         nv.now = i+1;
    //         nv.path.push_back(i+1);                                             //put this in path
    //         if(nv.level==n-1){
    //             int last;
    //             for(int k = 1; k<n; k++){
    //                 if(k==i)continue;
    //                 if(able[k]==1)last = k;
    //             }
    //             nv.path.push_back(last+1);
    //             nv.cost+=map[nv.now-1][last]; 
    //             nv.cost+=map[last][0];                                      //go back to 1
    //             if(nv.cost<optimal_c){
    //                 optimal_c = nv.cost;
    //                 optiaml_p = nv.path;
    //             }
    //             continue;
    //         }
    //         else{
    //             nv.bound = calcbound(nv)+nv.cost;
    //             if(nv.bound > optimal_c){
    //                 continue;
    //             }
    //             PQ.push(nv);
    //         }
            
            
    //     }
    // }
    // cout<<optimal_c<<endl;
    // vector<int>::iterator end = optiaml_p.end();
    // for(vector<int>::iterator it = optiaml_p.begin(); it != end; ++it){
    //     cout << *it << " ";
    // }
    // cout << endl;
    
	// int end_time = GetTickCount();
    // cout << "time:" << (end_time - star_time) << "ms." << endl<<"-----------\n";
    // return 0;
}