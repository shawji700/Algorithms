#include<iostream>
#include<vector>

using namespace std;

int binary_search(vector<int>& arr, int start, int end, int key){
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            start = mid + 1;
        else 
            end = mid - 1;
    }
    return -1;
}

int main(){
    // number of test case input is "T"
    int T;
    cin >> T;
    while(T--)
    {
        // first array length
    	int n; 
    	cin >> n;
    	vector<int> a(n);
        // first array numbers input, like:- 2 5 7 10 12 15
    	for(int i = 0; i < n; i++)
    		cin>>a[i];
        // second array length
        int m;
        cin >> m;
        vector<int> b(m);
        // second array numbers input, like:- 1 4 11 12 16
        for(int i = 0; i < m; i++)
    		cin>>b[i];
        int key = (n + m) / 2;
        int ele_in_a = binary_search(a, 0, n - 1, key);
        int ele_in_b = binary_search(b, 0, m - 1, key);
        if(ele_in_a != -1)
            cout << "Index of a :- " << ele_in_a << "\n";
        if(ele_in_b != -1)
            cout << "Index of b :- " << ele_in_b << "\n";
        if(ele_in_a == -1 && ele_in_b == -1)
            cout << "Element is not present";
    }
    return 0;
}