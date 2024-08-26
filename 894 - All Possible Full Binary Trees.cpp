/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> solve(int n, unordered_map<int, vector<TreeNode*>> &dp)
    {
        if(n == 1)
        return dp[n] = {new TreeNode()};

        if(dp.find(n) != dp.end())
        return dp[n];

        vector<TreeNode*> res;
        // going till n - 1 because one node will be taken up by root
        // i=i+2 because subtree number of nodes will always be even for FBT(full binary tree) to exist
        for(int i=1; i<n; i+=2)
        {
            vector<TreeNode*> leftTree = solve(i, dp);
            vector<TreeNode*> rightTree = solve(n - 1 - i, dp);

            for(auto &left: leftTree)
            {
                for(auto &right: rightTree)
                {
                    TreeNode* root = new TreeNode(0, left, right);
                    res.push_back(root);
                }
            }
        }

        return dp[n] = res;
    }

    vector<TreeNode*> allPossibleFBT(int n) 
    {   
        // dp map to store tree possible for each integer
        unordered_map<int, vector<TreeNode*>> dp;
        return solve(n, dp);
    }
};
