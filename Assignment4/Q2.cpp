// Write an OpenMP program such that, it should print the sum of square of the thread id’s. Also make sure that, each thread should print the square value of their thread id
#include <iostream>
#include <omp.h>
#include <iomanip>
using namespace std;

int main() {
    int n = 8; 

    int seq_sum = 0;
    double start_seq = omp_get_wtime();
    for (int i = 0; i < n; i++) {
        int sq = i * i;
        cout << "Sequential -> Thread " << i << " square = " << sq << endl;
        seq_sum += sq;
    }
    double end_seq = omp_get_wtime();

    int par_sum = 0;
    double start_par = omp_get_wtime();
    #pragma omp parallel num_threads(n) reduction(+:par_sum)
    {
        int tid = omp_get_thread_num();
        int sq = tid * tid;
        cout << "Parallel -> Thread " << tid << " square = " << sq << endl;
        par_sum += sq;
    }
    double end_par = omp_get_wtime();

    double seq_time = end_seq - start_seq;
    double par_time = end_par - start_par;

    cout << fixed << setprecision(9);
    cout << "\nSequential Sum = " << seq_sum 
         << " | Time = " << seq_time << " sec" << endl;
    cout << "Parallel Sum   = " << par_sum 
         << " | Time = " << par_time << " sec" << endl;
    cout << "Speedup = " << (par_time > 0 ? seq_time / par_time : 0) << "x" << endl;

    return 0;
}
