#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    int n;
    cout << "Enter size of vectors: ";
    cin >> n;

    vector<double> A(n), B(n);
    for (int i = 0; i < n; i++) {
        A[i] = i * 1.5;
        B[i] = i * 2.0;
    }

    cout << "------------Without reduction ----------------------" << endl;

    double sum = 0.0;
    double start = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        sum += A[i] * B[i];   
    }
    double end = omp_get_wtime();
    cout << "Dot Product (no reduction) = " << sum << endl;
    cout << "Time Taken = " << (end - start) << " seconds\n";


    cout << "\n------------Using reduction ----------------------" << endl;

    sum = 0.0;
    start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += A[i] * B[i];
    }

    end = omp_get_wtime();

    cout << "Dot Product (with reduction) = " << sum << endl;
    cout << "Time Taken = " << (end - start) << " seconds\n";

    return 0;
}
