#include <stdio.h>
#include <mpi.h>
#include<math.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // The initial values, u_i = i^2; v_i = log(i+1)
  int u_i = rank*rank;
  int v_i = rank*2+1;

  // Computing the intermediate value
  int tmp = u_i * v_i;

  // Reducing on process 0 :
  int result;
  MPI_Reduce(&tmp, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    //std::cout << "The reduced value is " << result << std::endl;
    printf("reduced value is %d\n",result);

    // Checking the result
    int validation = 0;
    int i;
    for (i=0; i < size; ++i)
      validation += i*i * (i*2+1);

    //std::cout << "Validation gives the value : " << validation << std::endl;
    printf("validation gives the value : %d\n",validation);
  }
  
  MPI_Finalize();
  
  return 0;
}
