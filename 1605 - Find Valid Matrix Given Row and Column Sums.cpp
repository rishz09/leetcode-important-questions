class Solution {
public:
    vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum) 
    {
        // greedy approach to put min(rowSum, colSum) in each cell so that conditions are satisfied 
        // automatically.
        // After each insertion, decrement rowSum and colSum by that inserted number so that we 
        // know the remaining rowSum and colSum for conditions to be satisfied.

        int r = rowSum.size(), c = colSum.size();
        vector<vector<int>> res(r, vector<int> (c, 0));

        // this loop automatically takes care of cases where r != c so no need to worry
        for(int i=0; i<r; i++)
        {
            for(int j=0; j<c; j++)
            {
                int mini = min(rowSum[i], colSum[j]);
                res[i][j] = mini;

                rowSum[i] -= mini;
                colSum[j] -= mini;
            }
        }

        return res;
    }
};
