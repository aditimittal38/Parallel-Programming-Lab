// Implementation of calculation of Pi using OpenMP.
#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    long long N = 100000000;  
    long long inside_seq = 0, inside_par = 0;
    double pi_seq, pi_par;
    double start, end;

    srand(time(0));

    // ---------------- SEQUENTIAL ----------------
    start = omp_get_wtime();
    for (long long i = 0; i < N; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1.0) inside_seq++;
    }
    pi_seq = 4.0 * inside_seq / (double)N;
    end = omp_get_wtime();
    double time_seq = end - start;
    cout << "Sequential Pi = " << pi_seq 
         << " | Time = " << time_seq << " sec" << endl;

    // ---------------- PARALLEL ----------------
    start = omp_get_wtime();
    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num() + time(0); // thread-private seed
        long long local_count = 0;
        #pragma omp for
        for (long long i = 0; i < N; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;
            if (x * x + y * y <= 1.0) local_count++;
        }
        #pragma omp atomic
        inside_par += local_count;
    }
    pi_par = 4.0 * inside_par / (double)N;
    end = omp_get_wtime();
    double time_par = end - start;
    cout << "Parallel Pi   = " << pi_par 
         << " | Time = " << time_par << " sec" << endl;

    // ---------------- SPEEDUP ----------------
    cout << "Speedup = " << time_seq / time_par << "x" << endl;

    return 0;
}
