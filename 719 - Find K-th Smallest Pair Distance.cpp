class Solution {
public:
    int numberOfPairs(int maxDiff, vector<int> &nums)
    {
        // 2 pointer approach.
        // Within a range [i, j], find pairs having diff <= maxDiff, with the ending point being j.
        // This ensures no duplicates.
        // Basically, we increase j until nums[j] - nums[i] > maxDiff. Within that subarray, all pairs are valid.
        // Now, if difference increases, just increase i till difference is <= maxDiff again

        int i = 0;
        int n = nums.size();
        
        int c = 0;
        for(int j = 0; j<n; j++)
        {
            while(nums[j] - nums[i] > maxDiff)
            ++i;

            c += j - i;
        }

        return c;
    }

    int smallestDistancePair(vector<int>& nums, int k) 
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        // we need to apply binary search on differences
        // for a difference value "mid", we need to find out number of pairs having difference <= mid
        // If number of pairs > k, it can still be the required value.
        // Why?
        // Consider difference value d gives (k - 1) number of pairs, and difference value d + 1 gives
        // (k + 2) number of pairs. We don't get exactly k pairs.
        // But wait. Difference value d + 1 contains k + 2 pairs, so it will also contain atleast k pairs.
        // Difference value d cannot contain k pairs because it contains MAXIMUM k - 1 pairs.
        // So d + 1 is our answer. Basically, when we get number of pairs > k, we CANNOT do h = mid - 1
        // because that mid might be our actual answer, as demonstrated above.
        // So, do h = mid for that case.
        // We can do l = mid + 1 though.

        // min difference is 0, and max difference is max element in array
        int l = 0, h = nums[n - 1];

        // Neetcode's approach (works)
        // while(l < h)
        // {
        //     int mid = (l + h) / 2;
        //     int count = numberOfPairs(mid, nums);

        //     if(count >= k)
        //     h = mid;

        //     else
        //     l = mid + 1;
        // }

        // My approach -> This works because in the end, l = mid + 1 returns back to the answer that was
        // previously held by h
        while(l <= h)
        {
            int mid = (l + h) / 2;
            int count = numberOfPairs(mid, nums);

            if(count >= k)
            h = mid - 1;

            else
            l = mid + 1;
        }
        
        return l;
    }
};
