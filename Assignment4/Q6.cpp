// Write a Parallel C program which should print the series of 2  and 4. Make sure both should be executed by different threads !

#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int n = 10;

    #pragma omp parallel num_threads(2)
    {
        int tid = omp_get_thread_num();

        if (tid == 0) {
            cout << "Thread " << tid << " printing multiples of 2:" << endl;
            for (int i = 1; i <= n; i++) {
                cout << "2 * " << i << " = " << 2 * i << endl;
            }
        }

        if (tid == 1) {
            cout << "Thread " << tid << " printing multiples of 4:" << endl;
            for (int i = 1; i <= n; i++) {
                cout << "4 * " << i << " = " << 4 * i << endl;
            }
        }
    }

    return 0;
}
