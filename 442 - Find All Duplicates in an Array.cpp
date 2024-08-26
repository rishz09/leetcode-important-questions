class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) 
    {
        // need to use original array as some sort of hashmap
        // now, for a value in a cell, its corresponding hash cell can be its (value - 1)
        // Since, the array is 0 indexed and values can be from 1 to n.
        // Now, whatever value we have in the hashcell, make it negative. This ensures that a particular 
        // value has been visited, and also the fact that the value in the hashcell CAN BE OBTAINED
        // later, by just taking absolute value.
        // We need abs of hashcell value because we need to mark that value's hashcell as well, if not marked
        // already.
        // Now, if a hashcell value is already -ve and is being visited again, then the value which 
        // corresponds to the hashcell is the duplicate element.

        //Eg: [2, 3, 4, 2]
        // -> [2, -3, 4, 2]  // hashcell of 2 = 2 - 1 = 1
        // -> [2, -3, -4, 2] // hashcell of abs(-3) = 3 - 1 = 2
        // -> [2, 3, -4, 2] // hashcell of abs(2) = 1 and that cell was already visited. so 2 is duplicate

        int n = nums.size();
        vector<int> res;

        for(int i=0; i<n; i++)
        {
            int hashIdx = abs(nums[i]) - 1;

            if(nums[hashIdx] < 0)
            res.push_back(abs(nums[i]));

            nums[hashIdx] *= -1;
        }

        return res;
    }
};
