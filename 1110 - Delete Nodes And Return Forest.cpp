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
    void dfs(TreeNode* ptr, bool isRoot, vector<TreeNode*> &roots, unordered_set<int> &toDel)
    {
        if(!ptr)
        return;

        if(toDel.find(ptr->val) != toDel.end())
        {
            // true means that ptr->left and ptr->right are possible roots
            dfs(ptr->left, true, roots, toDel);
            dfs(ptr->right, true, roots, toDel);
        }

        else
        {
            // isRoot is only true when its parent had to be deleted and this current node doesn't have
            // to be deleted
            if(isRoot)
            roots.push_back(ptr);

            TreeNode* leftNode = ptr->left;
            TreeNode* rightNode = ptr->right;

            if(ptr->left && toDel.find(ptr->left->val) != toDel.end())
            ptr->left = nullptr;
            
            if(ptr->right && toDel.find(ptr->right->val) != toDel.end())
            ptr->right = nullptr;

            dfs(leftNode, false, roots, toDel);
            dfs(rightNode, false, roots, toDel);
        }
    }

    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) 
    {
        unordered_set<int> toDel;
        for(auto node: to_delete)
        toDel.insert(node);

        vector<TreeNode*> roots;

        // sending in as true because Tree's root is a potential root, if it itself doesn't have to be 
        // deleted
        dfs(root, true, roots, toDel);

        return roots;
    }
};
