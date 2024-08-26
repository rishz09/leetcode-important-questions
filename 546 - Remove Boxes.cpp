class Solution {
public:
    int solve(int i, int j, int count, vector<int> &boxes, vector<vector<vector<int>>> &dp)
    {
        if(i > j)
        return 0;

        while(i + 1 <= j && boxes[i] == boxes[i + 1])
        {
            ++count;
            ++i;
        }

        // now count stores the maximum number of same colored boxes (either consecutive or after skipping)
        count += 1;

        if(dp[i][j][count] != -1)
        return dp[i][j][count];

        // proceed to the next index with count 0 as we will get different colour
        int maxi = count * count + solve(i + 1, j, 0, boxes, dp);

        for(int k=i+1; k<=j; k++)
        {
            // if after skipping few indices, we get the same colour again, then jump to that with the current
            // count
            if(boxes[k] == boxes[i])
            {
                // calculates value of same colour boxes if it skips above other boxes
                int valAfterSkip = solve(k, j, count, boxes, dp);

                // recursively calculates the value of the middle elements which it had skipped
                int valBetweenSkip = solve(i + 1, k - 1, 0, boxes, dp);

                maxi = max(maxi, valAfterSkip + valBetweenSkip);
            }
        }

        return dp[i][j][count] = maxi;
    }

    int removeBoxes(vector<int>& boxes) 
    {
        // https://youtu.be/_8hSyaxVRZ8?si=Jzqh560nC5FA2xz5
        int n = boxes.size();

        // {left, right, count}
        vector<vector<vector<int>>> dp(n, vector<vector<int>> (n, vector<int> (n + 1, -1)));
        return solve(0, n - 1, 0, boxes, dp);
    }
};
