class Solution {
public:
    int solve(int k, int n, vector<vector<int>> &dp)
    {
        if(n == 0 || n == 1)
        return n;

        // if only one egg left, in the worst case we have to check from 0th floor to uppermost floor in
        // order to be certain
        if(k == 1)
        return n;

        if(dp[k][n] != -1)
        return dp[k][n];

        int l = 0, h = n;
        int mini = INT_MAX;
        while(l <= h)
        {
            int mid = (l + h) / 2;

            int breaks = 1 + solve(k - 1, mid - 1, dp);
            // instead of making l = mid + 1, we make n = n - mid because height is not relative over here.
            // we are just concerned about number of floors left to search. There is no concept such as indexes
            // of arrays over here so doesn't matter. And it makes DP ARRAY EASIER to construct.
            int notBreaks = 1 + solve(k, n - mid, dp);

            mini = min(mini, max(breaks, notBreaks));
            
            // confused as to why h = mid - 1 when notBreaks gives lower
            // maybe because we need worst case scenario?
            if(breaks > notBreaks)
            h = mid - 1;

            else l = mid + 1;
        }

        return dp[k][n] = mini;
    }

    int superEggDrop(int k, int n) 
    {
        // need to use dp + binary search to figure out all possible combos
        // dp[i][j] = minimum moves to be CERTAIN about the floor when floors are j and eggs remaining are i
        vector<vector<int>> dp(k + 1, vector<int> (n + 1, -1));
        return solve(k, n, dp);
    }
};
