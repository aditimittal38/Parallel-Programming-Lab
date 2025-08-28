// Write an OpenMP program where multiple threads increment a shared counter inside a loop.
// Implement once without synchronization (observe wrong result).
// Implement again using #pragma omp critical (correct result).


#include <iostream>
#include <omp.h>
using namespace std;
int main(){
    int counter = 0;
    #pragma omp parallel
    {
        cout << counter ++ << "from thread: " << omp_get_thread_num()<< endl;
    }

    cout << "Final Value: "<< counter<< endl;
    cout << "------------------With critical--------------"<< endl;

    counter = 0;
    #pragma omp parallel
    {
        #pragma omp critical
        {
            cout << counter ++ << "from thread: " << omp_get_thread_num()<< endl;
        }
        
    }
    cout << "Final Value: "<< counter<< endl;


}