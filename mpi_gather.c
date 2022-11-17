#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);
    // Get number of processes and check that 4 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(size != 4) {
        printf("This application is meant to be run with 4 MPI processes.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }
 
    // Determine root's rank
    int root_rank = 0;
    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 
    // Define my value
 
    int my_value[2];
    my_value[0] = my_rank * 100;
    my_value[1] = my_rank;
    printf("Process %d, my value = %d, %d.\n", my_rank, my_value[0], my_value[1]);
 
    if(my_rank == root_rank) {
        int buffer[8];
        MPI_Gather(&my_value, 2, MPI_INT, buffer, 2, MPI_INT, root_rank, MPI_COMM_WORLD);
        printf("Values collected on process %d: %d, %d, %d, %d, %d, %d, %d, %d.\n", my_rank, buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
    } else {
        MPI_Gather(&my_value, 2, MPI_INT, NULL, 0, MPI_INT, root_rank, MPI_COMM_WORLD);
    }
 
    MPI_Finalize();
    return 0;
}
