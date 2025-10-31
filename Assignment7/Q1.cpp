/*
MPI INstallation on Fedora
sudo dnf install openmpi openmpi-devel
echo 'export PATH=/usr/lib64/openmpi/bin:$PATH' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/lib64/openmpi/lib:$LD_LIBRARY_PATH' >> ~/.bashrc
source ~/.bashrc
mpicc --version
mpiexec --version


To run the code:
mpic++ Q1.cpp -o Q1
mpiexec -n 10 ./Q1

*/
/*
Q1. Implement a simple hello world program by setting number of processes equal to 10
*/


#include <mpi.h>
#include <iostream>
using namespace std; 

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    cout << "Hello World from process " << world_rank << " out of " << world_size << " processes" << endl;

    MPI_Finalize();
    return 0;
}
