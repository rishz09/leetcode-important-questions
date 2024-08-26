class Solution {
public:
    int solve(int i, vector<int> &unique, unordered_map<int, int> &freq, vector<int> &dp)
    {
        // now this is similar to House Robber problem
        if(i >= unique.size())
        return 0;

        // we multiply by frequency because, suppose if we take one occurrence, we can later that
        // occurrences of that same element without deleting num - 1 and num + 1, since they already have
        // been deleted

        if(dp[i] != -1)
        return dp[i];

        int pick = INT_MIN;
    
        if(i + 1 < unique.size() && unique[i] + 1 == unique[i + 1])
        pick = (unique[i] * freq[unique[i]]) + solve(i + 2, unique, freq, dp);

        else 
        pick = (unique[i] * freq[unique[i]]) + solve(i + 1, unique, freq, dp);
        
        int notPick = solve(i + 1, unique, freq, dp);

        return dp[i] = max(pick, notPick);
    }

    int deleteAndEarn(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());

        // creating a unique matrix to iterate easily in recursive method
        vector<int> unique;
        unordered_map<int, int> freq;

        for(int val: nums)
        {
            if(unique.size() == 0)
            unique.push_back(val);

            else if(unique.back() != val)
            unique.push_back(val);

            ++freq[val];
        }

        // dp[i] represents maximum obtainable points from [0, i]
        vector<int> dp(nums.size(), -1);
        return solve(0, unique, freq, dp);
    }
};
