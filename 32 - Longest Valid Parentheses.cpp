class Solution {
public:
    int longestValidParentheses(string s) 
    {
        int open = 0, close = 0;
        int l = s.length();

        if(l == 0)
        return 0;

        int maxi = 0;

        for(int i=0; i<l; i++)
        {
            if(s[i] == '(')
            ++open;

            else if(s[i] == ')')
            ++close;

            // do not reset open and close to zero here because we might get a case like ()() which is valid
            if(open == close)
            maxi = max(maxi, 2 * open);

            // we will never recover from this case so reset the counts
            else if(close > open)
            {
                open = 0;
                close = 0;
            }
        }


        // Traverse from l-1 to 0 to consider cases like (().
        // This is done because open is never equal to close if we traverse from left to right

        open = 0, close = 0;
        for(int i=l-1; i>=0; i--)
        {
            if(s[i] == '(')
            ++open;

            else if(s[i] == ')')
            ++close;

            if(open == close)
            maxi = max(maxi, 2 * open);

            // checking for this because we will encounter closing brackets first. If open becomes greater
            // than closing, it will never be recovered
            else if(open > close)
            {
                open = 0;
                close = 0;
            }
        }

        return maxi;
    }
};
