#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
public:
    int findMedian(vector<int> &arr, int start, int n)
    {
        sort(arr.begin() + start, arr.begin() + start + n);
        return arr[start + n / 2];
    }

    int foo(vector<int> &arr, int low, int high)
    {
        int n = high - low + 1;

        if (n <= 9)
        {
            return findMedian(arr, low, n);
        }

        vector<int> medians((n + 8) / 9);
        int k = 0;

        for (int i = 0; i < n / 9; i++)
        {
            arr[i] = findMedian(arr, low + i * 9, 9);
            k++;
        }

        if (n % 9 != 0)
        {
            arr[k] = findMedian(arr, low + (n / 9) * 9, n % 9);
        }

        return foo(arr, 0, k);
    }

    int find_median(vector<int> &v)
    {
        int low = 0, high = v.size() - 1;
        return foo(v, low, high);
    }
};

int main()
{
    // Number of test cases
    int T;
    cin >> T;
    while (T--)
    {
        // array length
        int n;
        cin >> n;
        vector<int> v(n);
        // array input integers like :- 4 12 8 3 1
        for (int i = 0; i < n; i++)
            cin >> v[i];
        Solution ob;
        int ans = ob.find_median(v);
        cout << ans << "\n";
    }
    return 0;
}