// Addition of Scalar value with a vector using static scheduling
#include <iostream>
#include <omp.h>
#include <vector>
#include <iomanip>
using namespace std;
int main(){

    int vector_size;
    cout << "Enter size of vector: ";
    cin >> vector_size;
    vector<double> vectorA(vector_size);

    int scalarVal;
    cout << "Enter Scalar Value: " ;
    cin >> scalarVal;

    for (int i = 0; i< vector_size ; i++){
        vectorA[i] = i*3.0;
    }

    double start_seq, start_static, start_dynamic, end_seq, end_static, end_dynamic;

    omp_set_num_threads(4);

    cout << " ----------------------------Sequential------------------------------------------- "<<endl;

    start_seq = omp_get_wtime();
    for (int i = 0; i < vector_size; i++) {
        vectorA[i] += scalarVal;
    }
    end_seq = omp_get_wtime();


    cout << " ----------------------------Static------------------------------------------- "<<endl;

    start_static = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i< vector_size; i++){
        vectorA[i] += scalarVal;
        // #pragma omp critical
        // {
        //     cout << "Index " << i << " updated to " << vectorA[i] << " by thread " << omp_get_thread_num() << endl;
        // }
        
    }
    end_static = omp_get_wtime();


    cout << " -----------------------------Dynamic------------------------------------------ "<<endl;
    start_dynamic = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i< vector_size; i++){
        vectorA[i] += scalarVal;
        // #pragma omp critical
        // {
        //     cout << "Index " << i << " updated to " << vectorA[i] << " by thread " << omp_get_thread_num() << endl;
        // }
    }
    end_dynamic = omp_get_wtime();

    cout << fixed << setprecision(9);
    double seq_time = end_seq - start_seq;
    double static_time = end_static - start_static;
    double dynamic_time = end_dynamic - start_dynamic;

    cout << "\n--------------------------- Performance Summary -----------------" << endl;
    cout << "Sequential Time: " << seq_time << " seconds" << endl;
    cout << "Static Time:     " << static_time << " seconds" << endl;
    cout << "Dynamic Time:    " << dynamic_time << " seconds" << endl;

    cout << "\nSpeedup (Static vs Seq):  " << seq_time / static_time << endl;
    cout << "Speedup (Dynamic vs Seq): " << seq_time / dynamic_time << endl;


    
}