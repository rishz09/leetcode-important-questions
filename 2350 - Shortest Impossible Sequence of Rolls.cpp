class Solution {
public:
    int shortestSequence(vector<int>& rolls, int k) 
    {
        // Approach: starting from 0, we find the smallest index where all numbers from 1 to k is present.
        // This implies that any subsequence of length 1 is possible.
        // Then starting from the next index, find the same again.
        // This implies that any subsequence of length 2 is possible.
        // Now, if length 3 cannot be obtained, this means that there is atleast one element which, after
        // a valid a subsequence of length 2, cannot be obtained.

        int n  = rolls.size();
        int c = 0;

        unordered_set<int> st;

        for(int ele: rolls)
        {
            st.insert(ele);
            if(st.size() == k)
            {
                ++c;
                // clear because you again want to find shortest subsequence where all numbers from 1 to k
                // are present 
                st.clear();
            }
        }

        return c + 1;
    }
};
