#include <bits/stdc++.h>
using namespace std;

class Solution {
    int timer;
    vector<int> disc, low;
    vector<vector<int>> adj;
    vector<vector<int>> bridges;

public:
    void dfs(int u, int parent) {
        disc[u] = low[u] = timer++;

        for(int v : adj[u]) {

            if(v == parent) continue;   // ignore parent edge

            if(disc[v] == -1) {   // not visited
                dfs(v, u);

                low[u] = min(low[u], low[v]);

                // Bridge condition
                if(low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            }
            else {
                // Back edge
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    vector<vector<int>> findBridges(int V, vector<vector<int>>& edges) {

        adj.resize(V);
        disc.assign(V, -1);
        low.assign(V, -1);
        timer = 0;

        // Build graph
        for(auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Run DFS for all components
        for(int i = 0; i < V; i++) {
            if(disc[i] == -1)
                dfs(i, -1);
        }

        return bridges;
    }
};
