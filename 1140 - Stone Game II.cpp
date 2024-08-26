class Solution {
public:
    // this function will return Alice's maximum possible score, given both play optimally
    int solve(bool alice, int i, int m, vector<int> &piles, vector<vector<vector<int>>> &dp)
    {
        // unique DP problem
        if(i >= piles.size())
        return 0;

        if(dp[alice][i][m] != -1)
        return dp[alice][i][m];

        int res = (alice) ? 0 : INT_MAX;
        int total = 0;

        for(int j=1; j<=2*m; j++)
        {
            // handling edge case
            if(i + j > piles.size())
            break;

            total += piles[i + j - 1];

            // when it is alice's turn, she wants to maximise her score
            if(alice)
            res = max(res, total + solve(!alice, i + j, max(m, j), piles, dp));

            // when it is bob's turn, he wants to minimize Alice's score
            else
            res = min(res, solve(!alice, i + j, max(m, j), piles, dp));
        }

        return dp[alice][i][m] = res;
    }
    int stoneGameII(vector<int>& piles) 
    {
        // 3D DP required.
        // {alice or bob, cur idx, cur M}
        int n = piles.size();
        vector<vector<vector<int>>> dp(2, vector<vector<int>> (n + 1, vector<int> (n + 1, -1)));
        return solve(true, 0, 1, piles, dp);    
    }
};
