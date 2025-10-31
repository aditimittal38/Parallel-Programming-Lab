/*
Write a MPI program to find the sum of all the elements of an array A of size
n. Elements of an array can be divided into two equals groups. The first [n/2]
elements are added by the first process, P0, and last [n/2] elements the by second process, P1. The two sums then are added to get the final result.
*/
/*
mpic++ Q4.cpp -o Q4
mpiexec -n 2 ./Q4
*/
#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 10;
    int A[n] = {1,2,3,4,5,6,7,8,9,10}; 

    int local_sum = 0;
    int half = n / 2;
    if (rank == 0){
        for (int i = 0; i < half; i++){
            local_sum += A[i];
        }
        MPI_Send(&local_sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } 
    else if (rank == 1){
        for (int i = half; i < n; i++){
            local_sum += A[i];
        }
        int sum0;
        MPI_Recv(&sum0, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int total_sum = local_sum + sum0;
        cout << "Total sum of array elements = " << total_sum << endl;
    }
    MPI_Finalize();
    return 0;
}