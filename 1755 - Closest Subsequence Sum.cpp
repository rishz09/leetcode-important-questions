class Solution {
public:
    void genSubsetSum(int i, int j, int res, vector<int> &nums, vector<int> &arr)
    {
        if(i == j + 1)
        {   
            arr.push_back(res);
            return;
        }

        // take condition
        genSubsetSum(i + 1, j, res + nums[i], nums, arr);

        // not take condition
        genSubsetSum(i + 1, j, res, nums, arr);
    }

    int meetInTheMiddle(vector<int> &nums, int goal)
    {
        int n = nums.size();
        
        vector<int> left, right;
        genSubsetSum(0, n/2, 0, nums, left);
        genSubsetSum(n/2 + 1, n - 1, 0, nums, right);

        // sorting right array and simply comparing using lower bound
        // no need to sort the other array as we need to do linear search on it anyways
        sort(right.begin(), right.end());

        int minDiff = INT_MAX;
        int lSize = left.size();
        int rSize = right.size();

        for(int i=0; i<lSize; i++)
        {
            int reqdDiff = goal - left[i];
            int idx = lower_bound(right.begin(), right.end(), reqdDiff) - right.begin();

            if(idx != rSize)
            minDiff = min(minDiff, abs(goal - left[i] - right[idx]));

            if(idx > 0)
            minDiff = min(minDiff, abs(goal - left[i] - right[idx - 1]));
        }

        return minDiff;
    }

    int minAbsDifference(vector<int>& nums, int goal) 
    {
        // Meet in the middle approach
        // For brute force recursion, generating all subsets require o(2^n), which gives TLE for n = 40
        // Meet in the middle divides the original array into 2 equal parts, generates all subsets, 
        // and applies binary search to have overall TC as O(N. 2^(N/2))

        return meetInTheMiddle(nums, goal);
    }
};
