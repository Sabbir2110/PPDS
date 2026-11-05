//Producer–Consumer System


#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    int rank, item;
    int data[8]={10,20,30,40,50,60,70,80};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {

        for(int i=0; i<8; i++) {
            int dest = (i%2)+1;
            item = data[i];

            cout << "P0 produced: " << item << endl;

            MPI_Send(&item,1,MPI_INT,dest,0,
                     MPI_COMM_WORLD);
        }

        item = -1;

        MPI_Send(&item,1,MPI_INT,1,0,MPI_COMM_WORLD);
        MPI_Send(&item,1,MPI_INT,2,0,MPI_COMM_WORLD);

        int ack;

        for(int i=0; i<8; i++) {
            MPI_Recv(&ack,1,MPI_INT,MPI_ANY_SOURCE,1,
                     MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }

        cout << "All 8 items processed successfully."
             << endl;
    }
    else {

        while(true) {
            MPI_Recv(&item,1,MPI_INT,0,0,
                     MPI_COMM_WORLD,MPI_STATUS_IGNORE);

            if(item == -1)
                break;

            cout << "P" << rank
                 << " consumed: " << item << endl;

            int ack = 1;

            MPI_Send(&ack,1,MPI_INT,0,1,MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
