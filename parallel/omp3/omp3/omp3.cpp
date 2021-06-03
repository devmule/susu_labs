#include <iostream>
using namespace std;
#include <omp.h>
void main()
{
    int k;
    cin >> k;
    omp_set_num_threads(k);
#pragma omp parallel
    {
        if (omp_get_thread_num() % 2 == 0)
            printf("I am %d thread from %d threads!\n", omp_get_thread_num(), omp_get_num_threads());
    }
}