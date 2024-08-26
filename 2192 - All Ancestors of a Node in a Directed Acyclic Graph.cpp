class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) 
    {
        // apply toposort, then insert current node and the current list of ancestors to its neighbours
        int l = edges.size();
        vector<vector<int>> adj(n);
        for(int i=0; i<l; i++)
        adj[edges[i][0]].push_back(edges[i][1]);

        vector<int> indegree(n, 0);

        for(int i=0; i<l; i++)
        {
            int from = edges[i][0];
            int to = edges[i][1];

            ++indegree[to];
        }

        queue<int> q;
        for(int i=0; i<n; i++)
        {
            if(indegree[i] == 0)
            q.push(i);
        }

        vector<int> topo;
        while(!q.empty())
        {
            int node = q.front();
            q.pop();
            
            topo.push_back(node);
            for(int child: adj[node])
            {
                --indegree[child];
                if(indegree[child] == 0)
                q.push(child);
            }
        }
        
        vector<vector<int>> res(n);
        for(int i=0; i<n; i++)
        {
            int node = topo[i];
            for(int child: adj[node])
            {
                // apply merging two sorted arrays procedure
                vector<int> temp = res[child];
                int l1 = temp.size(), l2 = res[node].size();

                res[child] = {};
                int j = 0, k = 0;
                while(j != l1 && k != l2)
                {
                    if(temp[j] < res[node][k])
                    {
                        res[child].push_back(temp[j]);
                        ++j;
                    }

                    else if(temp[j] > res[node][k])
                    {
                        res[child].push_back(res[node][k]);
                        ++k;
                    }

                    else
                    {
                        res[child].push_back(temp[j]);
                        ++j;
                        ++k;
                    }
                }

                while(j != l1)
                {
                    res[child].push_back(temp[j]);
                    ++j;
                }

                while(k != l2)
                {
                    res[child].push_back(res[node][k]);
                    ++k;
                }

                j = 0;
                int size = res[child].size();
                if(size == 0 || node < res[child][0])
                {
                    res[child].insert(res[child].begin(), node);
                    continue;
                }

                bool f = false;
                for(int j=1; j<size; j++)
                {
                    if(res[child][j - 1] < node && res[child][j] > node)
                    {
                        res[child].insert(res[child].begin() + j, node);
                        f = true;
                        break;
                    }
                }

                if(!f)
                res[child].push_back(node);
            }
        }

        return res;
    }
};
