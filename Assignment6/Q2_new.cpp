#include <iostream>
#include <omp.h>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int N = 10000000;  // vector size
    vector<float> A(N), B(N);
    
    // Initialize vectors
    for (int i = 0; i < N; i++) {
        A[i] = i * 0.5f;
        B[i] = i * 0.25f;
    }

    double start, end;
    float dot_seq = 0.0, dot_parallel = 0.0, dot_reduction = 0.0, dot_critical = 0.0, dot_atomic = 0.0;

    // ===================== 1. SEQUENTIAL =====================
    start = omp_get_wtime();
    for (int i = 0; i < N; i++)
        dot_seq += A[i] * B[i];
    end = omp_get_wtime();
    double time_seq = end - start;
    cout << fixed << setprecision(6);
    cout << "Sequential Dot Product = " << dot_seq 
         << " | Time = " << time_seq << " s\n";

    // ===================== 2. PARALLEL (manual sum) =====================
    int num_threads;
    float partial_sum[64] = {0.0}; // support up to 64 threads
    start = omp_get_wtime();
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < N; i++)
            partial_sum[tid] += A[i] * B[i];
    }
    num_threads = omp_get_num_threads();
    for (int t = 0; t < num_threads; t++)
        dot_parallel += partial_sum[t];
    end = omp_get_wtime();
    double time_parallel = end - start;
    cout << "Parallel (manual sum) Dot Product = " << dot_parallel 
         << " | Time = " << time_parallel 
         << " | Speedup = " << time_seq / time_parallel << "x\n";

    // ===================== 3. PARALLEL (reduction) =====================
    start = omp_get_wtime();
    #pragma omp parallel for reduction(+:dot_reduction)
    for (int i = 0; i < N; i++)
        dot_reduction += A[i] * B[i];
    end = omp_get_wtime();
    double time_reduction = end - start;
    cout << "Parallel (reduction) Dot Product = " << dot_reduction 
         << " | Time = " << time_reduction 
         << " | Speedup = " << time_seq / time_reduction << "x\n";

    // ===================== 4. PARALLEL (critical) =====================
    start = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        float temp = A[i] * B[i];
        #pragma omp critical
        dot_critical += temp;
    }
    end = omp_get_wtime();
    double time_critical = end - start;
    cout << "Parallel (critical) Dot Product = " << dot_critical 
         << " | Time = " << time_critical 
         << " | Speedup = " << time_seq / time_critical << "x\n";

    // ===================== 5. PARALLEL (atomic) =====================
    start = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        float temp = A[i] * B[i];
        #pragma omp atomic
        dot_atomic += temp;
    }
    end = omp_get_wtime();
    double time_atomic = end - start;
    cout << "Parallel (atomic) Dot Product = " << dot_atomic 
         << " | Time = " << time_atomic 
         << " | Speedup = " << time_seq / time_atomic << "x\n";

    return 0;
}
