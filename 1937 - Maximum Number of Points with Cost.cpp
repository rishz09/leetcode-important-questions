class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) 
    {
        // look at Neetcode's vid or my rough copy work to get an understanding of the DP solution
        int r = points.size();
        int c = points[0].size();    

        vector<long long> temp(c);
        for(int i=0; i<c; i++)
        temp[i] = points[0][i];

        long long res = 0;
        if(r == 1)
        {
            for(int i=0; i<c; i++)
            res = max(res, temp[i]);

            return res;
        }

        for(int i=1; i<r; i++)
        {
            vector<long long> left(c), right(c);

            // filling up left array
            left[0] = temp[0];
            for(int j=1; j<c; j++)
            left[j] = max(left[j - 1] - 1, temp[j]);

            // filling up right array
            right[c - 1] = temp[c - 1];
            for(int j=c-2; j>=0; j--)
            right[j] = max(right[j + 1] - 1, temp[j]);

            // updating max value
            for(int j=0; j<c; j++)
            {
                long long maxVal = max(left[j], right[j]);
                temp[j] = points[i][j] + maxVal;

                if(i == r - 1)
                res = max(res, temp[j]);
            }
        }

        return res;
    }
};
