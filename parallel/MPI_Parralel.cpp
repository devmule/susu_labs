#include <iostream>
#include "mpi.h"

using namespace std;

/*
	1)
	Поток - это исполняемый код, который имеет собственный стек и часть контекста процесса (регистры)
	Процесс - это выполняющийся экземпляр программы, владеющий системными ресурсами (памятью, открытыми файлами, атрибутами безопасности)

	2)
	создается 2 потока, 

	3)
	
	*/

int main(int argc, char *argv[])
{
	int rank, n, send, recieve;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) 
	{ 
		printf("\nHello from process %3d\n", rank);
		cin >> send;
		MPI_Send(&send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else
	{
		printf("\nHello from process %3d\n", rank);
		MPI_Recv(&recieve, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		cout << recieve;
	}
		
	MPI_Finalize();
	return 0;
}
