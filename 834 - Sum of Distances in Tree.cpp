class Solution {
public:
    int totalNodes;
    void dfsPartialSumAndNodes(int root, vector<vector<int>> &adj, vector<bool> &vis, vector<int> &nodeCount,
    vector<int> &dist)
    {
        vis[root] = true;

        // checking for leaf node
        if(adj[root].size() == 1 && vis[adj[root][0]] == true)
        {
            nodeCount[root] = 1;
            dist[root] = 0;
            return;
        }

        for(int node: adj[root])
        {
            if(!vis[node])
            {
                dfsPartialSumAndNodes(node, adj, vis, nodeCount, dist);
                dist[root] += dist[node] + nodeCount[node];
                nodeCount[root] += nodeCount[node];
            }
        }

        // counting itself
        nodeCount[root] += 1;
    }

    void dfsForCompleteDistance(int root, int parent, vector<vector<int>> &adj, vector<bool> &vis, vector<int> &nodeCount,
    vector<int> &dist)
    {
        vis[root] = true;

        // using the formula derived in notebook
        if(parent != -1)
        dist[root] = dist[parent] + (totalNodes - nodeCount[root]) - nodeCount[root];

        for(int node: adj[root])
        {
            if(!vis[node])
            dfsForCompleteDistance(node, root, adj, vis, nodeCount, dist);
        }
    }


    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) 
    {
        // Watch Aryan Mittal's video or my notes
        // Beautiful concept of DP on trees / graphs
        totalNodes = n;
        int m = edges.size();
        vector<vector<int>> adj(n);

        for(int i=0; i<m; i++)
        {
            int a = edges[i][0];
            int b = edges[i][1];

            adj[a].push_back(b);
            adj[b].push_back(a);
        }     

        vector<bool> vis(n, false);
        vector<int> nodeCount(n, 0), dist(n, 0);

        // after this dfs, only root of tree has complete distance calculation
        // all other nodes have partial distance (only child subtrees distances)
        dfsPartialSumAndNodes(0, adj, vis, nodeCount, dist);

        // reinitializing
        fill(vis.begin(), vis.end(), false);

        // dfs to calculate complete distances of all nodes by re-rooting
        dfsForCompleteDistance(0, -1, adj, vis, nodeCount, dist);
        return dist;
    }
};
