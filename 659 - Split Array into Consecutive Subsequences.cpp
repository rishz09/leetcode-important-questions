class Solution {
public:
    bool isPossible(vector<int>& nums) 
    {
        int n = nums.size();

        // using a frequency map to store freq of all nums
        // a second map is used to store the next possible number for an already created subsequence,
        // as well as the frequency, indicating how many such joins will be possible for an already created
        // subsequence

        unordered_map<int, int> freq;
        for(int ele: nums)
        ++freq[ele];

        unordered_map<int, int> nextPossible;
        for(int ele: nums)
        {
            if(freq[ele] != 0)
            {
                if(nextPossible.find(ele) != nextPossible.end())
                {
                    --nextPossible[ele];
                    if(nextPossible[ele] == 0)
                    nextPossible.erase(ele);

                    // now ele + 1 becomes the next possible joinable number to subsequence
                    ++nextPossible[ele + 1];
                    --freq[ele];
                }

                // this is checking if we can create a subsequence of length 3 which starts at ele
                // checking this greedily works because:
                // suppose we didn't do this check for ele = 1, which is the lowest number in array.
                // now, if we didn't perform check for this, there is no way where ele = 1 will be checked for
                // again since we are always checking for new subsequences where elements are consecutive.
                // In that case, ele = 1 will always have to be the starting element of a subsequence
                else if(freq[ele + 1] > 0 && freq[ele + 2] > 0)
                {
                    --freq[ele];
                    --freq[ele + 1];
                    --freq[ele + 2];

                    ++nextPossible[ele + 3];
                }
            }
        }

        // if all elements frequency is zero, then there exists atleast one such combo of subsequences, 
        // where all elements will be included, else not possible
        for(auto p: freq)
        {
            if(p.second != 0)
            return false;
        }    

        return true;
    }
};
