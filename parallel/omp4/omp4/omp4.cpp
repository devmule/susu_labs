#include <iostream>
using namespace std;
#include <omp.h>
#include <windows.h>

int main() {
    int k, rank;
    std::cin >> k;
    omp_set_num_threads(k);

#pragma omp parallel private(rank)
    {
       rank = omp_get_thread_num();
        Sleep(100);
        printf("I am %d thread.\n", rank);

   }
    system("pause");
   return 0;
}