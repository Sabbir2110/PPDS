//Global Histogram Using MPI_Allreduce


#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank;

    int data[4][4] = {
        {1,2,2,3},
        {2,3,4,4},
        {1,4,5,5},
        {0,2,5,9}
    };

    int local[10]={0};
    int global[10]={0};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for(int i=0; i<4; i++)
        local[data[rank][i]]++;

    MPI_Allreduce(local,global,10,MPI_INT,
                  MPI_SUM,MPI_COMM_WORLD);

    if(rank == 0) {

        cout << "Value   Frequency" << endl;

        for(int i=0; i<10; i++)
            cout << i << "       " << global[i] << endl;
    }

    MPI_Finalize();
    return 0;
}
