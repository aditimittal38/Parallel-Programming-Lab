#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;
int main(){
    while(1){
        cout<<"Enter number of threads: ";
        int n;
        cin >> n;
        int vector_size;
        cout << "Enter size of vector: ";
        cin >> vector_size;
        vector<double> vectorA(vector_size);
        vector<double> vectorB(vector_size);
        vector<double> vectorC(vector_size);
        for (int i = 0; i< vector_size ; i++){
            vectorA[i] = i*3.0;
            vectorB[i] = i*2.0;
        }

        omp_set_num_threads(n);
        // or 
        // Environment variable: export OMP_NUM_THREADS=4
        // Command line: OMP_NUM_THREADS=4 ./a.out
        // Inside code: omp_set_num_threads(n);
        double start = omp_get_wtime();
        #pragma omp parallel 
        {
            #pragma omp single
            cout << "Total number of threads: " << omp_get_num_threads() << endl;

            #pragma omp for        
            for (int i = 0; i < vector_size ; i++){
                vectorC[i] = vectorA[i] + vectorB[i];
                // #pragma omp critical
                // {
                //     cout << i << "th index Calculated by: " << omp_get_thread_num() << endl;
                // }
                
            }
        }
        
    
        double end = omp_get_wtime();
        cout << "Total time: " << end - start << endl;
    
        cout << "Do you want to enter more values? (0/1) " ;
        int flag;
        cin >> flag; 
        if (flag==0){
            break;
        }
    }
}