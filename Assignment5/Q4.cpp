// Write a program to print numbers from 1 to 20 in ascending order using a parallel for loop.
// Use #pragma omp ordered to maintain order.
// Run the same code without ordered and compare the output.

#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int N = 20;

    cout << "---------Without ordered --------" << endl;
    #pragma omp parallel for
    for (int i = 1; i <= N; i++) {
        cout << i << " ";
    }
    cout << endl;

    cout << "---------With ordered ---------" << endl;
    #pragma omp parallel for ordered
    for (int i = 1; i <= N; i++) {
        #pragma omp ordered
        cout << i << " ";
    }
    cout << endl << endl;

    

    return 0;
}
