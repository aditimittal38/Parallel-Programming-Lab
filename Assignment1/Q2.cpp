#include <iostream>
#include <omp.h>
using namespace std;
int main(){
    int num_of_threads;
    cout<< "Enter number of threads: ";
    cin >> num_of_threads;
    omp_set_num_threads(num_of_threads);
    #pragma omp parallel 
    {
        cout<<"Hello World from thread " << omp_get_thread_num() << endl;
    }
}