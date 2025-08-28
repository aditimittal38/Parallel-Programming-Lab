// Write a program to compute the sum of an array of N=10^6 numbers in parallel.
// First, use #pragma omp atomic to update the shared sum.
// Compare runtime with #pragma omp critical.


#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;
int main(){
    int n = 1000000;
    vector<double> arr(n);
    for (int i=0; i<n; i++){
        arr[i] = i*1.26;
    }
    double sum = 0;
    cout << "------------------Without critical and atomic--------------"<< endl;

    #pragma omp parallel for
    for (int i=0 ;i<n; i++){
        sum += arr[i];
    }
    cout << "Final Value: "<< sum << endl;

    sum = 0;
    cout << "------------------With atomic--------------"<< endl;

    #pragma omp parallel for
    for (int i=0 ;i<n; i++){
        #pragma omp atomic
        sum += arr[i];
    }
    cout << "Final Value: "<< sum << endl;

    sum = 0;
    cout << "------------------With critical--------------"<< endl;

    #pragma omp parallel for
    for (int i=0 ;i<n; i++){
        #pragma omp critical
        {
            sum += arr[i];
        }
    }
    cout << "Final Value: "<< sum << endl;


}