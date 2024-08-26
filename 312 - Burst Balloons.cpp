class Solution {
public:
    int solve(int i, int j, vector<int> &nums, vector<vector<int>> &dp)
    {
        if(i > j)
        return 0;

        if(dp[i][j] != -1)
        return dp[i][j];

        // Striver adds two 1s in front and back of nums, but adding ele to front increases TC by O(n),
        // so doing condition wise checking
        int leftLim = (i == 0) ? 1 : nums[i - 1];
        int rightLim = (j == nums.size() - 1) ? 1 : nums[j + 1];

        int maxi = INT_MIN;
        for(int idx = i; idx<=j; idx++)
        {
            int coins = (leftLim * nums[idx] * rightLim) + 
                        solve(i, idx - 1, nums, dp) + // left partition
                        solve(idx + 1, j, nums, dp);  // right partition

            maxi = max(maxi, coins);
        }

        return dp[i][j] = maxi;
    }

    int maxCoins(vector<int>& nums) 
    {
        // This is noted down in my copy. Look at it for further explanation
        // start from last balloon burst as this will remove dependency of partitions on each other.
        // Eg: if we start from first balloon burst and arr is [b1 b2 b3 b4].
        // Burst b3
        // [b1 b2] [b4]. Now, bursting of b2 is dependent on b4, so dependent on other partition

        // Now, let us start from the last balloon burst
        // [1 b1 b2 b3 b4 1]
        // Last balloon burst = b3
        // [1 b1 b2] [b4 1]
        // Now, if we take second last balloon burst from [1 b1 b2], then coins = 1 x (b burst) x b3
        // If from second partition, then coins = b3 x (b burst) x 1
        // Therefore, the case where 2 balloons are left to be burst will look like this:
        // -> either [x b3] OR [b3 x]
        // -> either way, currently burst balloon is not dependent on other partition

        int n = nums.size();

        // dp[i][j] indicates max coins generated from i to j
        vector<vector<int>> dp(n, vector<int> (n, -1));
        return solve(0, n - 1, nums, dp);
    }
};
