class Solution {
public:
    void populateGraph(int n, vector<vector<int>> &arr, vector<string> &grid)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                char c = grid[i][j];
                if(c == '\\')
                {
                    arr[i * 4][j * 4] = 1;
                    arr[i * 4 + 1][j * 4 + 1] = 1;
                    arr[i * 4 + 2][j * 4 + 2] = 1;
                    arr[i * 4 + 3][j * 4 + 3] = 1;
                }

                else if(c == '/')
                {
                    arr[i * 4 + 3][j * 4] = 1;
                    arr[i * 4 + 2][j * 4 + 1] = 1;
                    arr[i * 4 + 1][j * 4 + 2] = 1;
                    arr[i * 4][j * 4 + 3] = 1;
                }
            }
        }
    }

    bool checkValidIndex(int i, int j, int n)
    {
        if(i >= 0 && i < (n * 4) && j >= 0 && j < (n * 4))
        return true;

        return false;
    }

    void dfsTraverse(int i, int j, int n, vector<vector<int>> &arr, vector<vector<int>> &coords)
    {
        arr[i][j] = 1;

        for(int k=0; k<4; k++)
        {
            if(checkValidIndex(i + coords[k][0], j + coords[k][1], n) && arr[i + coords[k][0]][j + coords[k][1]] == 0)
            dfsTraverse(i + coords[k][0], j + coords[k][1], n, arr, coords);
        }

    }


    int regionsBySlashes(vector<string>& grid) 
    {
        int n = grid.size();
        vector<vector<int>> arr(n * 4, vector<int> (n * 4, 0)); 
        vector<vector<int>> coords = {{0, 1},
                                      {0, -1},
                                      {1, 0},
                                      {-1, 0}};

        populateGraph(n, arr, grid);


        // for(int i=0; i<arr.size(); i++)
        // {
        //     for(int j=0; j<arr[i].size(); j++)
        //     cout << arr[i][j] << " ";
        //     cout << endl;
        // }

        int regions = 0;
        for(int i=0; i<n*4; i++)
        {
            for(int j=0; j<n*4; j++)
            {
                if(arr[i][j] != 1)
                {
                    dfsTraverse(i, j, n, arr, coords);
                    ++regions;
                }
            }
        }

        return regions;
    }
};
