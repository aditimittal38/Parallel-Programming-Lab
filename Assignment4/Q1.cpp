// Q1. Write an OpenMP program such that, it should print the name of your family members, such that the names should come from different threads/cores. Also print the respective job id.
#include <iostream>
#include <omp.h>
#include <iomanip>
using namespace std;

int main() {
    string names[] = {"Rakesh", "Ritu", "Tushar", "Me"};
    int n = sizeof(names) / sizeof(names[0]);

    double start_seq = omp_get_wtime();
    for (int i = 0; i < n; i++) {
        cout << "Seq -> " << names[i] << " (JobID: " << i << ")" << endl;
    }
    double end_seq = omp_get_wtime();

    double start_par = omp_get_wtime();
    #pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num();
        if (tid < n) {
            cout << "Thread " << tid << " -> " << names[tid] << " (JobID: " << tid << ")" << endl;
        }
    }
    double end_par = omp_get_wtime();

    double seq_time = end_seq - start_seq;
    double par_time = end_par - start_par;

    cout << fixed << setprecision(9);
    cout << "\nSequential Time: " << seq_time << " sec" << endl;
    cout << "Parallel Time:   " << par_time << " sec" << endl;
    cout << "Speedup: " << seq_time / par_time << "x" << endl;

    return 0;
}
