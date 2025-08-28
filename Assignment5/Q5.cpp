// Write a program with two parallel for loops inside the same parallel region:
// First loop initializes an array.
// Second loop immediately prints the array elements.
// Use #pragma omp for nowait on the first loop and observe what happens (incorrect output).
// Then remove nowait to fix the issue.


#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
    int N = 10;
    vector<int> arr(N, 0);

    cout << "---------Using nowait ---------" << endl;

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < N; i++) {
            arr[i] = i * 2;
        }
        #pragma omp for
        for (int i = 0; i < N; i++) {
            cout << arr[i] << " ";
        }
    }
    cout << endl << endl;

    cout << "---------Without nowait ---------" << endl;

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < N; i++) {
            arr[i] = i * 2;
        }

        #pragma omp for
        for (int i = 0; i < N; i++) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;

    return 0;
}
