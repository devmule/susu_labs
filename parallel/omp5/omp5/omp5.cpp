#include <iostream>
using namespace std;
#include <omp.h>

int main() {
    int k, n,sum = 0;
    std::cin >> k;
    std::cin >> n;
    int i;

#pragma omp parallel for reduction(+:sum) num_threads(k)
    for (i = 1; i <= n; i++)
    {
     sum += i;
      #pragma omp critical
        {
       std::cout << "[" << omp_get_thread_num() << "]: Sum = " << sum <<"\n";
       }    }

   std::cout << "sum = " << sum << std::endl;
    system("pause");
    return 0;

}