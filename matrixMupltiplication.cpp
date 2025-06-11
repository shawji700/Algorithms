#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int matrixMultiplication(vector<int> &arr)
{

    int n = arr.size();

    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 2; len < n; len++)
    {
        for (int i = 0; i < n - len; i++)
        {
            int j = i + len;
            dp[i][j] = 99999999;

            for (int k = i + 1; k < j; k++)
            {
                int cost = dp[i][k] + dp[k][j] + arr[i] * (2 * arr[k] - 1) * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[0][n - 1];
}

int main()
{
    cout << "Enter the number of test case: \n";
    int T;
    cin >> T;
    while (T--)
    {
        cout << "Enter the array size n: \n";
        int n;
        cin >> n;
        cout << "Enter the vector array of n size (with space-speration):\n";
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        cout << matrixMultiplication(arr) << "\n";
    }
    return 0;
}
