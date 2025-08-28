// Print hello world using, #pragma omp parallel and #pragma omp parallel for

#include <iostream>
#include <omp.h>
#include <iomanip>
using namespace std;
int main(){
    
    double start_seq = omp_get_wtime();
    for(int i=0; i<10; i++){
        cout << "Hello from sequential" <<endl;
    }
    double end_seq = omp_get_wtime();
    cout << " -------------------------------------------------------" << endl;


    omp_set_num_threads(4);
    double start_parallel = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        cout << "Total num of threads:" << omp_get_num_threads() << endl;
        cout << "Hello world from thread " << omp_get_thread_num() <<endl;
    }
    double end_parallel = omp_get_wtime();


    cout << " -------------------------------------------------------" << endl;
    // #pragma omp parallel
    // {
    //     #pragma omp single
    //     cout << "Total num of threads:" << omp_get_num_threads() << endl;

    //     for(int i=0; i<10; i++){
    //         cout << "Hello world from thread " << omp_get_thread_num() <<endl;
    //     }
        
    // }
    // cout << " -------------------------------------------------------" << endl;

    double start_parallel_for = omp_get_wtime();
    #pragma omp parallel for 
    for(int i=0; i<10; i++){
        cout << "Hello " << i << "world from thread " << omp_get_thread_num() <<endl;
    }
    double end_parallel_for = omp_get_wtime();

    double seq_time = end_seq - start_seq;
    double parallel_time = end_parallel - start_parallel;
    double parallel_for_time = end_parallel_for - start_parallel_for;

    cout << "------------------------------------------------------" << endl;
    cout << fixed << setprecision(9);
    cout << "Sequential time: "<< seq_time<<endl;
    cout << "Parallel time: "<<parallel_time<<endl;
    cout << "Parallel for time: "<< parallel_for_time <<endl;
    cout << "Speedup: "<<endl;
    cout << "Parallel: " << seq_time/parallel_time<<endl;
    cout << "Parallel for: " << seq_time/parallel_for_time<<endl;



}