//Deadlock Avoidence


#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, send, recv;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    send = (rank == 0) ? 100 : 200;

    MPI_Sendrecv(&send,1,MPI_INT,1-rank,0,
                 &recv,1,MPI_INT,1-rank,0,
                 MPI_COMM_WORLD,MPI_STATUS_IGNORE);

    cout << "P" << rank << " sent " << send
         << " and received " << recv << endl;

    MPI_Finalize();
    return 0;
}
