// Consider a scenario where you have a shared variable total_sum that needs to be updated concurrently by multiple threads in a parallel program. However, concurrent updates to this variable can result in data races and incorrect results. Your task is to modify the program to ensure correct synchronization using OpenMP's critical and atomic constructs.
// Note*:
// Implement a simple parallel program in C that initializes an array of integers and calculates the sum of its elements concurrently using OpenMP.
// Identify potential issues with concurrent updates to the total_sum variable in the parallelized version of the program.
// Modify the program to use OpenMP's critical/atomic directive to ensure synchronized access to the total_sum variable.
// Measure and compare the performance of synchronized versions against the unsynchronized implementation.
#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
    const int N = 1000000;
    vector<int> arr(N, 1); 

    long long total_sum = 0;
    double start, end;

    // ---------------- UNSYNCHRONIZED ----------------
    total_sum = 0;
    start = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        total_sum += arr[i];   
    }
    end = omp_get_wtime();
    cout << "Unsynchronized Sum   = " << total_sum 
         << " | Time = " << (end - start) << " sec" << endl;

    // ---------------- CRITICAL ----------------
    total_sum = 0;
    start = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp critical
        {
            total_sum += arr[i];
        }
    }
    end = omp_get_wtime();
    cout << "Critical Section Sum = " << total_sum 
         << " | Time = " << (end - start) << " sec" << endl;

    // ---------------- ATOMIC ----------------
    total_sum = 0;
    start = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        #pragma omp atomic
        total_sum += arr[i];
    }
    end = omp_get_wtime();
    cout << "Atomic Sum           = " << total_sum 
         << " | Time = " << (end - start) << " sec" << endl;

    return 0;
}

