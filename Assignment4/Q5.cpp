// Consider a scenario where you have to parallelize a program that performs matrix multiplication using OpenMP. Your task is to implement parallelization using both static and dynamic scheduling, and compare the execution time of each approach.
// Note*:
//  Implement a serial version of matrix multiplication in C/C++.
// Parallelize the matrix multiplication using OpenMP with static scheduling.
// Parallelize the matrix multiplication using OpenMP with dynamic scheduling.
// Measure the execution time of each parallelized version for various matrix sizes.
// Compare the execution times and discuss the advantages and disadvantages of static and dynamic scheduling in this context.

#include <iostream>
#include <omp.h>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int N;
    cout << "Enter matrix size (N x N): ";
    cin >> N;

    vector<vector<int>> A(N, vector<int>(N, 1));
    vector<vector<int>> B(N, vector<int>(N, 2));
    vector<vector<int>> C(N, vector<int>(N, 0));

    double start, end;

    // ---------------- SERIAL ----------------
    start = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    end = omp_get_wtime();
    double serial_time = end - start;
    cout << "Serial Time: " << serial_time << " sec" << endl;

    // ---------------- STATIC SCHEDULING ----------------
    C.assign(N, vector<int>(N, 0));
    start = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    end = omp_get_wtime();
    double static_time = end - start;
    cout << "Static Scheduling Time: " << static_time << " sec" << endl;
    cout << "Speedup (Static): " << serial_time / static_time << "x" << endl;

    // ---------------- DYNAMIC SCHEDULING ----------------
    C.assign(N, vector<int>(N, 0));
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    end = omp_get_wtime();
    double dynamic_time = end - start;
    cout << "Dynamic Scheduling Time: " << dynamic_time << " sec" << endl;
    cout << "Speedup (Dynamic): " << serial_time / dynamic_time << "x" << endl;

    return 0;
}
