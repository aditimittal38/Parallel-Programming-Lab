// Matrix Matrix Multiplication
#include <iostream>
#include <omp.h>
#include <vector>
#include <iomanip>
using namespace std;
int main(){
    int m, n;
    cout <<"Enter number of rows and columns ";
    cin >> n ;
    vector<vector<int>> A(n, vector<int>(n));
    vector<vector<int>> B(n, vector<int>(n));
    vector<vector<int>> C(n, vector<int>(n, 0));

    double start_seq, start_parallel, start_collapse, end_seq, end_parallel, end_collapse;

    for (int i = 0; i<n ;i ++){
        for (int j = 0; j<n; j++){
            A[i][j] = i*3.0 + j*2.0;
            B[i][j] = i*2.0 + j*1.5;
        }
    }

    cout<<"-----------------------Sequential----------------------"<< endl;
    start_seq = omp_get_wtime();
    for (int i = 0; i<n ; i++){
        for(int j = 0; j<n; j++){
            C[i][j] = 0;
            for(int k = 0; k<n; k++ ){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    end_seq = omp_get_wtime();


    cout<<"-----------------------Parallel----------------------" << endl;
    
    start_parallel = omp_get_wtime();
    #pragma omp parallel for 
    for (int i = 0; i<n ; i++){
        for(int j = 0; j<n; j++){
            C[i][j] = 0;
            for(int k = 0; k<n; k++ ){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    end_parallel = omp_get_wtime();

    cout<<"-----------------------Collapse----------------------" << endl;

    start_collapse = omp_get_wtime();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i<n ; i++){
        for(int j = 0; j<n; j++){
            C[i][j] = 0;
            for(int k = 0; k<n; k++ ){
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }

    end_collapse = omp_get_wtime();

    for (int i = 0; i<n ; i++){
        for(int j = 0; j<n; j++){
            cout << C[i][j] <<" ";
        }
        cout<<endl;
        
    }
    cout << fixed << setprecision(9);
    double seq_time = (end_seq - start_seq);
    double parallel_time = (end_parallel - start_parallel);
    double collapse_time = (end_collapse - start_collapse);

    cout << "Sequential Time: " << seq_time << " seconds\n";
    cout << "Parallel Time: " << parallel_time << " seconds\n";
    cout << "Collapse Time: " << collapse_time << " seconds\n";

    cout << "\n-----------------------Speedup----------------------" << endl;
    cout << "Parallel Speedup: " << seq_time / parallel_time << "x\n";
    cout << "Collapse Speedup: " << seq_time / collapse_time << "x\n";
}