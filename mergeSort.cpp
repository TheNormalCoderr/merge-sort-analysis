#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
using namespace std::chrono;

/* ---------------- MERGE FUNCTION ---------------- */
void merge(vector<int> &vec, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = vec[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            vec[k++] = L[i++];
        else
            vec[k++] = R[j++];
    }

    while (i < n1)
        vec[k++] = L[i++];

    while (j < n2)
        vec[k++] = R[j++];
}

/* ---------------- MERGE SORT ---------------- */
void mergeSort(vector<int> &vec, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

/* ---------------- MAIN ---------------- */
int main()
{
    const int START_SIZE = 10000;
    const int MAX_SIZE = 1000000;
    const int STEP_SIZE = 10000;
    const int TRIALS = 10;

    srand(time(nullptr));

    ofstream fout("mergesort_comparison.txt");
    fout << "ArraySize\tMergeSort_Time_us\n";

    for (int size = START_SIZE; size <= MAX_SIZE; size += STEP_SIZE)
    {
        double totalTime = 0;

        for (int t = 0; t < TRIALS; t++)
        {
            vector<int> arr(size);

            for (int i = 0; i < size; i++)
            {
                arr[i] = rand() % size;
            }

            auto start = high_resolution_clock::now();
            mergeSort(arr, 0, size - 1);
            auto end = high_resolution_clock::now();

            totalTime += duration<double, micro>(end - start).count();
        }

        double avgTime = totalTime / TRIALS;

        fout << size << "\t" << avgTime << "\n";

        cout << "Size: " << size
             << " | Merge Sort: " << avgTime << " µs\n";
    }

    fout.close();
    cout << "\nData saved to mergesort_comparison.txt\n";

    return 0;
}