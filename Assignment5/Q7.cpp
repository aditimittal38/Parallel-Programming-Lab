#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    long long N = 1000000;
    long long sum_seq = 0, sum_parallel = 0, sum_with_reduction = 0;

    double start_seq = omp_get_wtime();
    for(long long i = 1; i <= N; i++) {
        sum_seq += i * i;
    }
    double end_seq = omp_get_wtime();

    #pragma omp parallel for 
    for(long long i = 1; i <= N; i++) {
        sum_parallel += i * i;
    }

    double start_par = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum_with_reduction)
    for(long long i = 1; i <= N; i++) {
        sum_with_reduction += i * i;
    }
    double end_par = omp_get_wtime();

    cout << "Sum of squares (Sequential) = " << sum_seq << endl;
    cout << "Sequential Time = " << end_seq - start_seq << " seconds\n\n";

    cout << "Sum of squares (Parallel) = " << sum_parallel << endl;
    cout << "Sum of squares (With Reduction) = " << sum_with_reduction << endl;
    cout << "Parallel Time = " << end_par - start_par << " seconds\n";

    cout << "Speedup = " << (end_seq - start_seq) / (end_par - start_par) << "x" << endl;

    return 0;
}
