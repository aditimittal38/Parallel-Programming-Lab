/*
Q2: Implement a MPI program to give an example of Deadlock. 
*/
/*
mpic++ Q2.cpp -o Q2
mpiexec -n 2 ./Q2
*/

#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int msg;
    if (rank == 0) {
        // Process 0 waits to receive first
        MPI_Recv(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        // Process 1 also tries to receive first
        MPI_Recv(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    // both the processes wait to receive from each other endlessly and it causes a deadlock.

    // Correct Way to communicate without deadlock:
    // if (rank == 0) {
    //     MPI_Send(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    //     MPI_Recv(&msg, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // }
    // else if (rank == 1) {
    //     MPI_Recv(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    // }

    MPI_Finalize();
    return 0;
}
