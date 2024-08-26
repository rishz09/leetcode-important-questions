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
    int solve(TreeNode* ptr, unordered_map<TreeNode*, int> &dp)
    {
        if(!ptr)
        return 0;

        if(dp.find(ptr) != dp.end())
        return dp[ptr];

        int take = ptr->val;
        if(ptr->left)
        take += solve(ptr->left->left, dp) + solve(ptr->left->right, dp);

        if(ptr->right)
        take += solve(ptr->right->right, dp) + solve(ptr->right->left, dp);

        int notTake = solve(ptr->left, dp) + solve(ptr->right, dp);

        return dp[ptr] = max(take, notTake); 

    }

    int rob(TreeNode* root) 
    {
        unordered_map<TreeNode*, int> dp;
        return solve(root, dp);
    }
};
