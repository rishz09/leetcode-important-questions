class Solution {
public:
    bool isPossible(vector<int> &tasks, vector<int> &workers, int pills, int strength, int mid)
    {
        multiset<int> task(tasks.begin(), tasks.begin() + mid);
        multiset<int> work(workers.begin(), workers.begin() + mid);

        while(!task.empty())
        {
            // getting the lowest demanding task and highest strength worker among them
            int t = *task.begin();
            int w = *work.begin();

            if(w < t)
            {
                if(pills == 0)
                return false;

                w += strength;
                --pills;

                // finding upper bound of the new worker strength
                // upper bound gives pointer to that element which is just greater than that element
                auto it = task.upper_bound(w);
                
                // pointer points to task.begin(), it means that lower element doesn't exist, so task cannot
                // be done even with pills
                if(it == task.begin())
                return false;

                // decrementing pointer to get the index which has task strength <= worker strength, 
                // since we actually got upper bound
                --it;

                task.erase(it);
                work.erase(work.begin());
            }

            else
            {
                task.erase(task.begin());
                work.erase(work.begin());
            }
        }

        return true;
    }

    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) 
    {
        int n = tasks.size();
        int m = workers.size();

        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end(), greater<int>());

        // we will apply binary search over the number of tasks that can be completed
        // let mid = (l + h) / 2
        // take the minimum mid number of tasks and the highest mid number of workers.
        // now, start from the lowest strength worker. If he can't do the first task, give pills to him
        // If he still can't do any task, then mid number of tasks is NOT possible.
        // Why?
        // Higher strength workers might do some task, but that first worker will never complete a job,
        // thus mid tasks is impossible.

        int l = 1, h = min(n, m);

        int ans = -1;
        while(l <= h)
        {
            int mid = (l + h) / 2;

            // if possible, then lower number of tasks are also possible. So shift lower limit and check for 
            // higher number of tasks
            if(isPossible(tasks, workers, pills, strength, mid))
            {
                ans = mid;
                l = mid + 1;
            }

            else
            h = mid - 1;
        }

        return (ans == -1) ? 0 : ans;
    }
};
