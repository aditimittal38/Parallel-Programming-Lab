// Write an OpenMP program that calculates the partial sum of the first 20 natural numbers using parallelism. Each thread should compute a portion of the sum by iterating through a loop. Implement the program using the lastprivate clause to ensure that the final total sum is correctly computed and printed outside the parallel region.
// Hint: 
// 1.Utilize OpenMP directives to parallelize the summation process.
// 2.Ensure that each thread has its private copy of partial sum.
// 3.Use the lastprivate clause to assign the value of the last thread's partial sum to the final total sum after the parallel region.
#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int total_sum = 0;

    #pragma omp parallel for lastprivate(total_sum)
    for (int i = 1; i <= 20; i++) {
        int partial_sum = 0;
        for (int j = 1; j <= i; j++) {
            partial_sum += j;
        }
        total_sum = partial_sum;  
    }

    cout << "Final Sum of first 20 natural numbers = " << total_sum << endl;
    return 0;
}
