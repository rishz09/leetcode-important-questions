class Solution {
public:
    static bool customComp(const auto &p1, const auto &p2)
    {
        return p1.first > p2.first;
    }

    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) 
    {
        int n = nums1.size();
        vector<pair<int, int>> arr;

        for(int i=0; i<n; i++)
        arr.push_back({nums2[i], nums1[i]});

        // sort nums2 in descending order. 
        // Reason: Any number that comes after nums2[i] will become the number to be multiplied with,
        // since nums2[i + 1] < nums2[i] after sorting.
        // This makes it easier to consider elements from nums1 and nums2 as well.

        sort(arr.begin(), arr.end(), [&](const auto &p1, const auto &p2) {
            return customComp(p1, p2);
        });
        
        priority_queue<int, vector<int>, greater<int>> pq;
        long long sum = 0;
        long long maxi = LLONG_MIN;
        for(auto &p: arr)
        {
            int prod = p.first;
            int ele = p.second;

            // we push number nums1[i] inside minHeap.
            // Since we can take max k elements, in order to maximise the attribute, we need to remove lowest value
            // when we have considered k + 1 elements.
            // This can be ensured using minHeap. 
            // When we have considered k + 1 elements, remove the smallest element using pq.top(). Subtract it
            // from sum.
            
            pq.push(ele);

            sum += ele;
            if(pq.size() > k)
            {
                sum -= pq.top();
                pq.pop();
            }

            if(pq.size() == k)
            maxi = max(maxi, sum * prod);
        }

        return maxi;
    }
};
