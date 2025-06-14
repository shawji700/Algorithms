#include <iostream>
using namespace std;

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortTailRec(int arr[], int low, int high)
{
    while (low < high)
    {
        int pi = partition(arr, low, high);

        if (pi - low < high - pi)
        {
            quickSortTailRec(arr, low, pi - 1);
            low = pi + 1;
        }
        else
        {
            quickSortTailRec(arr, pi + 1, high);
            high = pi - 1;
        }
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int arr[] = {9, 4, 7, 3, 10, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    printArray(arr, n);

    quickSortTailRec(arr, 0, n - 1);

    cout << "Sorted array: ";
    printArray(arr, n);

    return 0;
}
