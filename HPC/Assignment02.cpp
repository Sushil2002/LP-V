#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
void BubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void ParallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
#pragma omp parallel for
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
void Merge(int l, int r, int mid, vector<int> &arr)
{
    int n1 = mid - l + 1;
    int n2 = r - mid;

    int a[n1], b[n2];
    for (int i = 0; i < n1; i++)
    {
        a[i] = arr[i + l];
    }
    for (int i = 0; i < n2; i++)
    {
        b[i] = arr[i + mid + 1];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 and j < n2)
    {
        if (a[i] < b[j])
        {
            arr[k] = a[i];
            i++;
        }
        else
        {
            arr[k] = b[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = a[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = b[j];
        j++;
        k++;
    }
}
void MergeSort(int l, int r, vector<int> &arr)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        MergeSort(l, mid, arr);
        MergeSort(mid + 1, r, arr);

        // Have to Merge sorted arrays
        Merge(l, r, mid, arr);
    }
}
void ParallelMergeSort(int l, int r, vector<int> &arr)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            MergeSort(l, mid, arr);
#pragma omp section
            MergeSort(mid + 1, r, arr);
        }
        // Have to Merge sorted arrays
        Merge(l, r, mid, arr);
    }
}
int main()
{
    int n = 10000;
    vector<int> arr(n);

    //One
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }

    auto start = high_resolution_clock::now();
    BubbleSort(arr);
    cout << endl;
    auto end = high_resolution_clock::now();
    auto sqbutime = duration_cast<milliseconds>(end - start);
//Two
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }
    start = high_resolution_clock::now();
    ParallelBubbleSort(arr);
    cout << endl;
    end = high_resolution_clock::now();
    auto pbutime = duration_cast<milliseconds>(end - start);
//Three
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }
    start = high_resolution_clock::now();
    MergeSort(0, n-1, arr);
    cout << endl;
    end = high_resolution_clock::now();
    auto sqmergetime = duration_cast<milliseconds>(end - start);
//Four
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }
    start = high_resolution_clock::now();
    ParallelMergeSort(0, n-1, arr);
    end = high_resolution_clock::now();
    auto pmergetime = duration_cast<milliseconds>(end - start);

    cout << "\nSequential bubble Sort Time - " << sqbutime.count() << " milliseocnds" << endl;
    cout << "Sequential Merge Sort Time - " << pbutime.count() << " milliseocnds" << endl;
    cout << "Parallel bubble Sort Time - " << sqmergetime.count() << " milliseocnds" << endl;
    cout << "Parallel Merge Sort Time - " << pmergetime.count() << " milliseocnds" << endl;
    return 0;
}