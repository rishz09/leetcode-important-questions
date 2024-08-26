class DisjointSet
{
    public:
    vector<int> parent, size;

    DisjointSet(int n)
    {
        parent.resize(n);
        for(int i=0; i<n; i++)
        parent[i] = i;

        size.resize(n, 1);
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

        else if(size[ulp_u] < size[ulp_v])
        {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }

        else
        {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution {
public:
    static bool customComp(vector<int> &a, vector<int> &b)
    {
        if(a[2] < b[2])
        return true;

        return false;
    }

    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) 
    {
        // using Disjoint set
        // Whoever has received the secret, will have it's ultimate parent the same (either 0 or firstPerson,
        // depends on the implementation)
        // Lastly, after all unions, iterate over parent vector to see who all have received the secret

        // sort meetings by ascending order of time 
        sort(meetings.begin(), meetings.end(), customComp);

        int len = meetings.size();

        DisjointSet ds(n);
        ds.unionBySize(0, firstPerson);
        int ultP = ds.findUPar(0);

        int j = 0;
        while(j != len)
        {
            vector<pair<int, int>> temp;
            int time = meetings[j][2];

            while(j != len && meetings[j][2] == time)
            {
                temp.push_back({meetings[j][0], meetings[j][1]});
                ++j;
            }

            bool f = true;
            while(f)
            {
                f = false;
                for(auto p: temp)
                {
                    int p1 = p.first;
                    int p2 = p.second;

                    if(ds.findUPar(p1) == ds.findUPar(p2))
                    continue;

                    else if(ds.findUPar(p1) == ultP || ds.findUPar(p2) == ultP)
                    {
                        f = true;
                        ds.unionBySize(p1, p2);
                    }
                }
            }
        }

        vector<int> res;
        for(int i=0; i<n; i++)
        {
            if(ds.findUPar(i) == ultP)
            res.push_back(i);
        }

        return res;
    }
};
