// Consider a variable called “Aryabhatta” declared as 10 (i.e int Arbhatta=10).Write an OpenMP program which should print the result of multiplication of thread id and value of the above variable. 
// Note*: The variable “Aryabhatta” should be declared as private
#include <iostream>
#include <omp.h>
using namespace std;

int main() {
    int Aryabhatta = 10;

    #pragma omp parallel private(Aryabhatta)
    {
        Aryabhatta = 10;
        int tid = omp_get_thread_num();
        int result = tid * Aryabhatta;
        cout << "Thread " << tid 
             << " * Aryabhatta(" << Aryabhatta << ") = " 
             << result << endl;
    }

    return 0;
}
