PQ.push(u);
    // cout << tmplb;
    node v;
    while(!PQ.empty()){
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