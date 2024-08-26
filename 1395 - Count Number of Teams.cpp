// DP solution
// class Solution {
// public:
//     int solve(int i, bool order, int size, int prev, vector<int> &rating, vector<vector<vector<int>>> &dp)
//     {
//         if(dp[i][order][size] != -1)
//         return dp[i][order][size];

//         if(size == 3)
//         return dp[i][order][size] = 1;

//         int n = rating.size();
//         if(i == n)
//         return dp[i][order][size] = 0;

//         int count = 0;
//         for(int j=i; j<n; j++)
//         {
//             if(order && rating[j] > prev)
//             count += solve(j + 1, order, size + 1, rating[j], rating, dp);

//             else if(!order && rating[j] < prev)
//             count += solve(j + 1, order, size + 1, rating[j], rating, dp);
//         }

//         return dp[i][order][size] = count;
//     }

//     int numTeams(vector<int>& rating) 
//     {
//         int n = rating.size();
//         // {index, order (ascending or descending), team size}
//         // bool order = true -> ascending, else descending
//         vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (2, vector<int> (4, -1)));

//         int count = 0;

//         // running a loop to change starting element of the team at every iteration
//         for(int i=0; i<n; i++)
//         {
//             int increasing = solve(i + 1, true, 1, rating[i], rating, dp);
//             int decreasing = solve(i + 1, false, 1, rating[i], rating, dp);

//             count += increasing + decreasing;
//         }

//         return count;
//     }
// };

// Greedy solution which starts from the middle element and count numbers at the left and right to it
class Solution {
public:
    int numTeams(vector<int> &rating)
    {
        int n = rating.size();
        int count = 0;

        for(int i=1; i<n; i++)
        {
            int leftLess = 0, rightLess = 0;
            int leftMore = 0, rightMore = 0;

            for(int j=0; j<i; j++)
            {
                if(rating[j] < rating[i])
                ++leftLess;
            }

            // holds because every number is unique, so no repititon
            leftMore = i - leftLess;

            for(int j=i + 1; j<n; j++)
            {
                if(rating[j] < rating[i])
                ++rightLess;
            }

            rightMore = (n - i - 1) - rightLess;
            count += leftLess * rightMore + leftMore * rightLess; 
        }

        return count;
    }
};
