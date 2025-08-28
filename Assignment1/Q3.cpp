// nproc = 8
// lscpu | grep "Mhz" 
// CPU(s) scaling MHz:                   22%
// CPU max MHz:                          4400.0000
// CPU min MHz:                          400.0000

#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main(){
    int N = 1e8;
    vector <double> A(N,1.5);
    vector <double> B(N,2.5);
    vector <double> C(N,1.6);
    double start_time = omp_get_wtime();

    #pragma parallel for
    for(int i=0; i<N; i++){
        C[i] = (A[i] + B[i]) + B[i] * A[i];
    }
    double end_time = omp_get_wtime();
    double flops = (3*N)/(end_time - start_time);
    cout << "FLOPS = "<< flops <<endl;
    
}