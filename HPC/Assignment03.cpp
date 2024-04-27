#include <bits/stdc++.h>
#include <iostream>
using namespace std::chrono;
using namespace std;
class Computation
{
public:
    void MinValue(vector<int> &arr)
    {
        int minval = arr[0];
        for (int i = 1; i < arr.size(); i++)
        {
            if (minval > arr[i])
            {
                minval = arr[i];
            }
        }
    }
    void MaxValue(vector<int> &arr)
    {
        int maxval = arr[0];
        for (int i = 1; i < arr.size(); i++)
        {
            if (maxval < arr[i])
            {
                maxval = arr[i];
            }
        }
    }
    void SumVal(vector<int> &arr)
    {
        int sum = 0;
        for (int i = 1; i < arr.size(); i++)
        {
            sum += arr[i];
        }
    }
};
class ParallelComputation
{
public:
    void MinValue(vector<int> &arr)
    {
        int minval = arr[0];
#pragma omp parallel for reduction(min : minval)
        for (int i = 1; i < arr.size(); i++)
        {
            if (minval > arr[i])
            {
                minval = arr[i];
            }
        }
    }
    void MaxValue(vector<int> &arr)
    {
        int maxval = arr[0];
#pragma omp parallel for reduction(max : maxval)
        for (int i = 1; i < arr.size(); i++)
        {
            if (maxval < arr[i])
            {
                maxval = arr[i];
            }
        }
    }
    void SumVal(vector<int> &arr)
    {
        int sum = 0;
#pragma omp parallel for reduction(+ : sum)
        for (int i = 1; i < arr.size(); i++)
        {
            sum += arr[i];
        }
    }
};
int main()
{
    Computation sc;
    ParallelComputation pp;
    int n = 1000000;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
    }
    // Sequntial
    auto start = high_resolution_clock::now();
    sc.MaxValue(arr);
    auto end = high_resolution_clock::now();
    auto sqmax = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    sc.MinValue(arr);
    end = high_resolution_clock::now();
    auto sqmin = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    sc.SumVal(arr);
    end = high_resolution_clock::now();
    auto sqsum = duration_cast<microseconds>(end - start);

    // Parallel
    start = high_resolution_clock::now();
    pp.MaxValue(arr);
    end = high_resolution_clock::now();
    auto ppmax = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    pp.MinValue(arr);
    end = high_resolution_clock::now();
    auto ppmin = duration_cast<microseconds>(end - start);

    start = high_resolution_clock::now();
    pp.SumVal(arr);
    end = high_resolution_clock::now();
    auto ppsum = duration_cast<microseconds>(end - start);

    cout << "\n+++++++++ TIME CALCULATION +++++++++" << endl
         << endl;
    cout << "\nSequential Max time - " << sqmax.count() << " milliseconds" << endl;
    cout << "Sequential Min time - " << sqmin.count() << " milliseconds" << endl;
    cout << "Sequential Sum time - " << sqsum.count() << " milliseconds" << endl;

    cout << "Parallel Max time - " << ppmax.count() << " milliseconds" << endl;
    cout << "Parallel Min time - " << ppmin.count() << " milliseconds" << endl;
    cout << "Parallel Sum time - " << ppsum.count() << " milliseconds" << endl;
    return 0;
}