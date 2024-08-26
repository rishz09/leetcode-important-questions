class Solution {
public:
    int n;
    int solve(int i, int j, string &s, vector<vector<int>> &dp)
    {
        // obviously 1 step needed to print 1 remaining character
        if(i == j)
        return 1;

        if(i > j)
        return 0;

        if(dp[i][j] != -1)
        return dp[i][j];

        int k = i + 1;
        while(k <= j && s[k] == s[i])
        ++k;

        // if this happens, all possible characters have been printed
        if(k == j + 1)
        return 1;

        // naive approach: after a different character has been found out, add 1 for all similar consecutive
        // characters which were found previously, and go the next character.
        int naiveApproach = 1 + solve(k, j, s, dp);

        int jumpApproach = INT_MAX;
        for(int l=k; l<=j; l++)
        {
            if(s[l] == s[i])
            {
                // if same character is found after few jumps, go that and continue printing
                int afterJump = solve(l, j, s, dp);
                // also solve the part we jumped over
                int betweenJump = solve(k, l - 1, s, dp);

                jumpApproach = min(jumpApproach, afterJump + betweenJump);
            }
        }

        return dp[i][j] = min(naiveApproach, jumpApproach);
    }

    int strangePrinter(string s) 
    {
        // One of the hardest problems of DP
        n = s.length();

        vector<vector<int>> dp(n, vector<int> (n, -1));
        return solve(0, n - 1, s, dp);
    }
};
