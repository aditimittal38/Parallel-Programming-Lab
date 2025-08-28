// Write a program to calculate factorial of n in parallel using OpenMP.
// Use critical or atomic for shared multiplication.
// Then optimize using reduction.

#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;
    double start, end;
    //-----------------Parallel without sync-----------
    start = omp_get_wtime();
    long long fact_parallel= 1;
    #pragma omp parallel for
    for (int i = 1; i <= n; i++) {
        fact_parallel *= i;
    }
    end = omp_get_wtime();
    cout<< "Without sync Time taken: "<< end - start<<endl;
    cout << "Factorial without synchronisation: " << fact_parallel << endl;

    // ---------------- Using critical ----------------
    start = omp_get_wtime();
    long long fact_critical = 1;
    #pragma omp parallel for
    for (int i = 1; i <= n; i++) {
        #pragma omp critical
        fact_critical *= i;
    }
    end = omp_get_wtime();
    cout<< "With critical Time taken: "<< end - start <<endl;
    cout << "Factorial using critical: " << fact_critical << endl;

    // ---------------- Using atomic ----------------
    start = omp_get_wtime();
    long long fact_atomic = 1;
    #pragma omp parallel for
    for (int i = 1; i <= n; i++) {
        #pragma omp atomic
        fact_atomic *= i;
    }
    end = omp_get_wtime();
    cout<< "With atomic Time taken: "<< end - start<<endl;
    cout << "Factorial using atomic: " << fact_atomic << endl;

    // ---------------- Using reduction ----------------
    start = omp_get_wtime();
    long long fact_reduction = 1;
    #pragma omp parallel for reduction(*:fact_reduction)
    for (int i = 1; i <= n; i++) {
        fact_reduction *= i;
    }
    end = omp_get_wtime();
    cout<< "With reduction Time taken: "<< end - start<<endl;
    cout << "Factorial using reduction: " << fact_reduction << endl;
    return 0;
}
