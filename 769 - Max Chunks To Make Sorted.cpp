class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) 
    {
        // Idea: Since numbers range from [0, n - 1], question becomes easier.
        // In sorted array index i must contain value i. Now, in the original array, if it isn't so, 
        // then find the index idx where the value i occurs. There HAS to be a chunk between [0, idx] for 
        // array to get sorted

        // Eg: [2, 0, 3, 1, 4]
        // Here, we NEED the chunk [2, 0, 3, 1] for 1 to get in its correct place
        // We also NEED to include till 1 because otherwise, 3 won't get inserted in its correct place
        // THIS is the approach. Find max till cur position. If curMax = value that should be in sorted array,
        // then till there we NEED a chunk

        int n = arr.size();
        int maxi = arr[0];

        vector<int> maxTillNow(n);
        maxTillNow[0] = maxi;

        for(int i=1; i<n; i++)
        {
            maxi = max(maxi, arr[i]);
            maxTillNow[i] = maxi;
        }     

        int c = 0;
        for(int i=0; i<n; i++)
        {
            if(maxTillNow[i] == i)
            ++c;
        }

        return c;
    }
};
