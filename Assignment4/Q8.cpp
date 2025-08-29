// Problem Statement 8:
// Consider a scenario where you have a large array of integers, and you need to find the sum of all its elements in parallel using OpenMP. The array is shared among multiple threads, and parallelism is needed to expedite the computation process. Your task is to write a parallel program that calculates the sum of all elements in the array using OpenMP's reduction clause.
// Note*:
// Implement a sequential version of the program that calculates the sum of all elements in the array without using any parallelism.
// Identify potential bottlenecks and limitations of the sequential implementation in handling large arrays efficiently.
// Modify the program to utilize OpenMP's reduction clause to parallelize the summation process across multiple threads.
// Test the program with different array sizes and thread counts to evaluate its scalability and performance.
// Discuss the advantages of using the reduction clause for parallel summation and its impact on program efficiency.

#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
    const int N = 100000000;   
    vector<int> arr(N, 1);     

    long long sum_seq = 0, sum_par = 0;
    double start, end;

    // ---------------- SEQUENTIAL ----------------
    start = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        sum_seq += arr[i];
    }
    end = omp_get_wtime();
    double time_seq = end - start;
    cout << "Sequential Sum = " << sum_seq 
         << " | Time = " << time_seq << " sec" << endl;

    // ---------------- PARALLEL (reduction) ----------------
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum_par)
    for (int i = 0; i < N; i++) {
        sum_par += arr[i];
    }
    end = omp_get_wtime();
    double time_par = end - start;
    cout << "Parallel Sum   = " << sum_par 
         << " | Time = " << time_par << " sec" << endl;

    // ---------------- SPEEDUP ----------------
    cout << "Speedup = " << time_seq / time_par << "x" << endl;

    return 0;
}

