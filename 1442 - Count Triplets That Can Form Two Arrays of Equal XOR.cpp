class Solution {
public:
    int countTriplets(vector<int>& arr) 
    {
        // if a = b, then their XOR gives 0.
        // So, if a subarray gives total xor as 0, then all non empty 2 way partitions can be a possible answer
        // Eg: Let x1 ^ x2 ^ x3 ^ x4 = 0.
        // Then, x1 = x2 ^ x3 ^ x4
        // x1 ^ x2 = x3 ^ x4
        // x1 ^ x2 ^ x3 = x4
        // In O(N^2) TC, go through all possible subarrays in the array and check

        // O(N) TC solution exists, but complicated. Search on youtube
        int n = arr.size();

        int count = 0;
        for(int i=0; i<n; i++)
        {
            int res = arr[i];
            for(int j=i+1; j<n; j++)
            {
                res = res ^ arr[j];
                if(res == 0)
                count += j - i;
            }
        } 

        return count;
    }
};
