class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) 
    {
        // if mod with k for 2 prefix sums are equal, they are a multiple of k
        // map stores modK value and index so that size can be compared.
        // once an index is stored, do not update it if the modK value occurs again, since we need
        // longer subarrays to verify size >= 2.
        // Eg: prefixsum = 2 and prefixsum = 7
        // Their mod values with 5 are 2 and 2, so subarray is divisble by 5.

        unordered_map<int, int> mp;
        mp[0] = -1;

        int prefixSum = 0, n = nums.size();
        for(int i=0; i<n; i++)
        {
            prefixSum += nums[i];
            int mod = prefixSum % k;

            if((mp.find(mod) != mp.end()) && (i - mp[mod] >= 2))
            return true;

            if(mp.find(mod) == mp.end())
            mp[mod] = i;
        }

        return false;
    }
};
