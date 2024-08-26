// Note: we shall use 18 bits loops while adding and deleting since max number of bits for 2 x 10 ^ 5 = 18
class Node
{
    private:
    Node* links[2];
    // used to keep track of number of times a number's particular bit is passing through this node.
    // easier for deletion
    int zero, one;

    public:
    Node()
    {
        for(int i=0; i<2; i++)
        links[i] = nullptr;

        zero = 0;
        one = 0;
    }

    void put(int bit, Node* node)
    {
        links[bit] = node;
    }

    bool containsKey(int bit)
    {
        return (links[bit] != nullptr);
    }

    Node* get(int bit)
    {
        return links[bit];
    }

    void increaseCount(int bit)
    {
        if(bit == 0)
        ++zero;

        else
        ++one;
    }

    int getCount(int bit)
    {
        return (bit == 0) ? zero : one;
    }

    void decreaseCount(int bit)
    {
        if(bit == 0)
        --zero;

        else
        --one;
    }
};

class Trie
{
    private:
    Node *root;
    
    public:
    Trie()
    {
        root = new Node();
    }

    void insert(int a)
    {
        Node* ptr = root;

        for(int i=17; i>=0; i--)
        {
            int bit = (a >> i) & 1;
            if(!ptr->containsKey(bit))
            ptr->put(bit, new Node());

            ptr->increaseCount(bit);
            ptr = ptr->get(bit);
        }
    }

    void deleteNum(int a)
    {
        Node* ptr = root;

        // the code is implemented in such that way the number will always be present.
        // So further checks not necessary
        for(int i=17; i>=0; i--)
        {
            int bit = (a >> i) & 1;
            ptr->decreaseCount(bit);

            Node* temp = ptr;
            ptr = ptr->get(bit);

            if(temp->getCount(bit) == 0)
            temp->put(bit, nullptr);

        }
    }

    int maximumXOR(int a)
    {
        Node* ptr = root;

        int res = 0;
        for(int i=17; i>=0; i--)
        {
            int bit = (a >> i) & 1;
            if(ptr->containsKey(1 - bit) && ptr->getCount(1 - bit) != 0)
            {
                res |= (1 << i);
                ptr = ptr->get(1 - bit);
            }

            else
            ptr = ptr->get(bit);
        }

        return res;
    }
};

class Solution {
public:
    void dfsFind(int node, vector<vector<int>> &adj, vector<int> &res, 
    unordered_map<int, vector<pair<int, int>>> &mp, Trie* trie)
    {
        trie->insert(node);

        if(mp.find(node) != mp.end())
        {
            for(auto p: mp[node])
            {
                int val = p.first;
                int idx = p.second;

                int maxi = trie->maximumXOR(val);
                res[idx] = maxi;
            }
        }

        for(int child: adj[node])
        dfsFind(child, adj, res, mp, trie);

        trie->deleteNum(node);
    }

    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) 
    {
        // Idea: Do preorder traversal (ideally this but we do not have a tree so have to do generalised
        // dfs, excluding the parent obviously). 
        // Use TRIE. Insert node value as we traverse. After traversing the children, remove the node value.
        // If node value is present in query, we can use trie to find out max XOR value as trie will only
        // contain values from root to that node (since we are removing nodes once its children have been traversed)

        // adjList containing only children
        int n = parents.size();
        vector<vector<int>> adj(n);

        int root = -1;
        for(int i=0; i<n; i++)
        {
            if(parents[i] == -1)
            root = i;

            else
            adj[parents[i]].push_back(i);
        }

        // storing node and index in query array and the given value.
        unordered_map<int, vector<pair<int, int>>> mp;
        int m = queries.size();
        for(int i=0; i<m; i++)
        {
            int node = queries[i][0];
            int val = queries[i][1];

            mp[node].push_back({val, i});
        }

        vector<int> res(m);

        Trie *trie = new Trie();
        dfsFind(root, adj, res, mp, trie);

        return res;
    }
};
