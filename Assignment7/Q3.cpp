/*
Implement blocking MPI send & receive to demonstrate Nearest neighbor exchange of data in a ring topology.
*/
/*
mpic++ Q3.cpp -o Q3
mpiexec -n 4 ./Q3
*/

#include <mpi.h>
#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int token;

    if (world_rank == 0) {
        token = -1;
    }

    int next = (world_rank + 1) % world_size;
    int prev = (world_rank - 1 + world_size) % world_size;

    if (world_rank != 0) {
        MPI_Recv(&token, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", world_rank, token, prev);
    }

    MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);

    if (world_rank == 0) {
        MPI_Recv(&token, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", world_rank, token, world_size - 1);
    }

    MPI_Finalize();
    return 0;
}
