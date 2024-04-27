#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
class Graph
{
public:
    void dfs(vector<int> adj[], vector<int> &vis, int v)
    {
        vis[v] = 1;
        for (int i = 0; i < adj[v].size(); i++)
        {
            if (vis[adj[v][i]] == 0)
            {
                dfs(adj, vis, adj[v][i]);
            }
        }
    }
    void bfs(vector<int> adj[], queue<int> &q, vector<int> &vis)
    {
        if (q.empty())
            return;
        int v = q.front();
        vis[v] = 1;
        q.pop();
        for (int i = 0; i < adj[v].size(); i++)
        {
            if (vis[adj[v][i]] == 0)
            {
                q.push(adj[v][i]);
                vis[adj[v][i]] = 1;
            }
        }
        bfs(adj, q, vis);
    }
};
class ParallelGraph
{
public:
    void dfs(vector<int> adj[], vector<int> &vis, int v)
    {
        vis[v] = 1;
        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); i++)
        {
            if (vis[adj[v][i]] == 0)
            {
                dfs(adj, vis, adj[v][i]);
            }
        }
    }
    void bfs(vector<int> adj[], queue<int> &q, vector<int> &vis)
    {
        if (q.empty())
            return;
        int v = q.front();
        vis[v] = 1;
        q.pop();
        #pragma omp parallel for
        for (int i = 0; i < adj[v].size(); i++)
        {
            if (vis[adj[v][i]] == 0)
            {
                q.push(adj[v][i]);
                vis[adj[v][i]] = 1;
            }
        }
        bfs(adj, q, vis);
    }
};
int main()
{
    int v;
    cout << "Enter the Number of Vertex - ";
    cin >> v;
    int e;
    cout << "Enter the Number of Edges - ";
    cin >> e;
    vector<int> adj[v];
    for (int i = 0; i < e; i++)
    {
        int u, v;
        cout << "Enter the value of u and v - ";
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> vis(v, 0);
    queue<int> q;
    Graph sg;
    ParallelGraph pg;
    //Sequential Time
    //1.dfs
    auto start = high_resolution_clock::now();
    sg.dfs(adj,vis,0);
    auto end = high_resolution_clock::now();
    auto sqdfstime = duration_cast<milliseconds>(end-start);


    for(int i=0;i<vis.size();i++){
        vis[i]=0;
    }
    //2.bfs
    start = high_resolution_clock::now();
    sg.bfs(adj,q,vis);
    end = high_resolution_clock::now();
    auto sqbfstime = duration_cast<milliseconds>(end-start);


    //Parallel
    //1.dfs
    for(int i=0;i<vis.size();i++){
        vis[i]=0;
    }
    start = high_resolution_clock::now();
    pg.dfs(adj,vis,0);
    end = high_resolution_clock::now();
    auto pdfstime = duration_cast<milliseconds>(end-start);

    //2.bfs
    for(int i=0;i<vis.size();i++){
        vis[i]=0;
    }
    q.empty();
    start = high_resolution_clock::now();
    pg.bfs(adj,q,vis);
    end = high_resolution_clock::now();
    auto pbfstime = duration_cast<milliseconds>(end-start);
    cout<<endl<<"+++++++++ TIME CALCULATIONS ++++++++"<<endl;
    cout<<"Sequential time for dfs - "<<sqdfstime.count()<<" millisecond"<<endl;
    cout<<"Sequential time for bfs - "<<sqbfstime.count()<<" millisecond"<<endl;
    cout<<"Parallel time for dfs - "<<pdfstime.count()<<" millisecond"<<endl;
    cout<<"Parallel time for bfs - "<<pbfstime.count()<<" millisecond"<<endl;

    return 0;
}