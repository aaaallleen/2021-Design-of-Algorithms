#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <windows.h>

using namespace std;

const int N = 31;

struct node
{
    int level;
    vector<int> path;
    float bound;
    int len;
};

struct cmp
{
    bool operator()(const node &x, const node &y)
    {
        return (x.bound == y.bound) ? (x.level < y.level) : x.bound > y.bound;
    }
};

vector<int> tour;
int minlength = 1000000;

int length(node u, int (*adj)[N])
{
    int sum = 0;
    for (int i = 0; i < u.path.size() - 1; i++)
    {
        sum += adj[u.path[i]][u.path[i + 1]];
    }
    return sum;
}

float bound(node nd, int now, int cities, int (*adj)[N])
{
    int able[N];
    for (int i = 1; i <= 30; i++)
        able[i] = 1;
    vector<int>::iterator end = nd.path.end();
    for (vector<int>::iterator it = nd.path.begin(); it != end; ++it)
    {
        able[*it] = 0;
    }
    able[now] = 1;
    int min = 10000000;
    int bound = 0;
    for (int i = 1; i <= cities; i++)
    {
        if (able[i] == 0)
            continue;
        for (int j = 1; j <= cities; j++)
        {
            if ((able[j] == 0 || j == now) && j != 1 && now != 1)
            {
            }
            else if (adj[i][j] < min && adj[i][j] != 0)
                min = adj[i][j];
        }
        if (min != 10000000)
        {
            bound += min;
        }
        min = 10000000;
    }
    return bound;
}

void TSP(int cities, int (*adj)[N])
{
    priority_queue<node, vector<node>, cmp> PQ;
    node u, v;

    while (!PQ.empty())
    {
        PQ.pop();
    }
    v.level = 0;
    v.path = {1};
    v.len = 0;
    v.bound = bound(v, v.path[v.path.size() - 1], cities, adj);
    PQ.push(v);
    while (!PQ.empty())
    {
        node top = PQ.top();
        PQ.pop();
        bool visit[N];

        memset(visit, false, sizeof(visit));
        for (int i = 1; i <= cities; i++)
        {
            vector<int>::iterator it = std::find(top.path.begin(), top.path.end(), i);
            if (it != top.path.end())
            {
                visit[i] = true;
            }
        }
        if (top.bound < minlength)
        {
            for (int i = 2; i <= cities; i++)
            {
                if (visit[i] == false && adj[top.path[top.path.size() - 1]][i] != 0)
                {
                    u.level = top.level + 1;
                    u.path = top.path;
                    u.path.push_back(i);
                    u.len = top.len + adj[top.path[top.path.size() - 1]][i];
                    if (u.level == cities - 2)
                    {
                        for (int j = 2; j <= cities; j++)
                        {
                            vector<int>::iterator it = std::find(top.path.begin(), top.path.end(), j);
                            if (it == top.path.end() && j != i)
                            {
                                u.path.push_back(j);
                                u.len += adj[u.path[u.path.size() - 1]][j];
                                break;
                            }
                        }
                        //u.path.push_back(1);
                        int path_len = u.len + adj[u.path[u.path.size() - 1]][1];
                        if (path_len < minlength)
                        {
                            minlength = path_len;
                            tour = u.path;
                        }
                    }
                    else
                    {
                        u.bound = bound(u, u.path[u.path.size() - 1], cities, adj) + u.len;
                        if (u.bound < minlength)
                        {
                            PQ.push(u);
                        }
                    }
                }
                else
                    continue;
            }
        }
        else
            break;
    }
}

int main()
{
    int cities = 0;
    int adj[N][N];

    cin >> cities;

    tour.reserve(cities + 1);

    for (int i = 1; i <= cities; i++)
    {
        for (int j = 1; j <= cities; j++)
        {
            cin >> adj[i][j];
        }
    }

    int star_time = GetTickCount();
    TSP(cities, adj);
    int end_time = GetTickCount();

    cout << minlength << endl;
    for (int i = 0; i < tour.size(); i++)
    {
        cout << tour[i] << " ";
    }
    cout << endl;
    cout << "time:" << (end_time - star_time) << "ms." << endl
         << "-----------\n";
}