class DisjointSet
{
    public:
    vector<int> parent, size;
    DisjointSet(int n)
    {
        parent.resize(n + 1);
        size.resize(n + 1, 1);

        for(int i=0; i<=n; i++)
        parent[i] = i;
    }

    int findUPar(int node)
    {
        if(node == parent[node])
        return node;

        return parent[node] = findUPar(parent[node]);
    }

    void unionBySize(int u, int v)
    {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);

        if(ulp_u == ulp_v)
        return;

        if(size[ulp_u] < size[ulp_v])
        {
            size[ulp_v] += size[ulp_u];
            parent[ulp_u] = ulp_v;
        }

        else
        {
            size[ulp_u] += size[ulp_v];
            parent[ulp_v] = ulp_u;
        }
    }
};

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) 
    {
        int len = edges.size();
        // keep two instances of disjoint set for alice and bob respectively.
        // add the type 3 edges at first, since adding them at the beginning means we have the option
        // to remove more edges.

        // approaching the problem in reverse. Adding instead of removing.

        DisjointSet alice(n), bob(n);
        vector<int> type1, type2;

        // adding type 3 edges
        int count = 0, n1 = 1, n2 = 1;
        for(int i=0; i<len; i++)
        {
            int type = edges[i][0];
            int u = edges[i][1];
            int v = edges[i][2];

            if(type == 1)
            {
                type1.push_back(i);
                continue;
            }

            if(type == 2)
            {
                type2.push_back(i);
                continue;
            }

            if(alice.findUPar(u) != alice.findUPar(v))
            {
                // alice and bob edge additions are equivalent as of now. so increment n2 as well.
                ++n1;
                ++n2;
                ++count;

                alice.unionBySize(u, v);
                bob.unionBySize(u, v);
            }
        }

        // adding alice only edges (type 1)
        for(auto &i: type1)
        {
            int u = edges[i][1];
            int v = edges[i][2];

            if(alice.findUPar(u) != alice.findUPar(v))
            {
                ++n1;
                ++count;
                alice.unionBySize(u, v);
            }
        }

        // adding type 2 edges for bob
        for(auto &i: type2)
        {
            int u = edges[i][1];
            int v = edges[i][2];

            if(bob.findUPar(u) != bob.findUPar(v))
            {
                ++n2;
                ++count;
                bob.unionBySize(u, v);
            }
        }

        if(n1 != n || n2 != n)
        return -1;

        return len - count;
    }
};
