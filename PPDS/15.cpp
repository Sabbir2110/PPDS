//Trapezoidal Rule (Numerical Integration)


#include <mpi.h>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double f(double x)
{
    return x*x;
}

int main(int argc, char *argv[])
{
    int rank, size, n=1000;

    double a=0, b=1, h;
    double local=0, total;
    double x1, x2;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    h = (b-a)/n;

    int start = rank*n/size;
    int end = (rank+1)*n/size;

    for(int i=start; i<end; i++) {

        x1 = a+i*h;
        x2 = a+(i+1)*h;

        local += (f(x1)+f(x2))*h/2;
    }

    MPI_Reduce(&local,&total,1,MPI_DOUBLE,
               MPI_SUM,0,MPI_COMM_WORLD);

    if(rank == 0) {

        double exact = 1.0/3.0;

        cout << fixed << setprecision(6);

        cout << "Numerical integral = " << total << endl;
        cout << "Exact integral = " << exact << endl;

        cout << "Absolute error = "
             << fabs(total-exact) << endl;
    }

    MPI_Finalize();
    return 0;
}
