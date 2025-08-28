// Write a program with two parallel regions:
// In the first part, each thread computes the square of its thread ID and stores it in an array.
// Use a #pragma omp barrier to ensure all threads finish before the master thread prints the array.

#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
    int num_threads = 4; 
    vector<int> arr(num_threads); 

    omp_set_num_threads(num_threads);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        arr[thread_id] = thread_id * thread_id; 

        #pragma omp barrier 

        #pragma omp master
        {
            cout << "Squares of thread IDs: ";
            for (int i = 0; i < num_threads; i++) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
