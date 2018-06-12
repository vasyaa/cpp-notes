#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

#include <cblas.h>
//#include <BLAS.h>
#include <cblas_f77.h>

//extern "C" {
//int dgemm_(char *, char *, int *, int *, int *, double *, double *, int *,
//        double *, int *, double *, double *, int *);
//}

void init(double* matrix, int row, int column) {
    for (int j = 0; j < column; j++) {
        for (int i = 0; i < row; i++) {
            matrix[j * row + i] = ((double) (i + j + 1));
        }
    }
}

void print(const char * name, const double* matrix, int row, int column) {
    printf("Matrix %s has %d rows and %d columns:\n", name, row, column);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%.3f ", matrix[j * row + i]);
        }
        printf("\n");
    }
    printf("\n");
}

int rowsA = 1024, colsB = 1024, common = 1024;
double* A;
double* B;
double* C;

void create_matices() {
    A = (double*) malloc(rowsA * common * sizeof(double));
    B = (double*) malloc(common * colsB * sizeof(double));
    C = (double*) malloc(rowsA * colsB * sizeof(double));

    assert(A != NULL);
    assert(B != NULL);
    assert(C != NULL);

    init(A, rowsA, common);
    init(B, common, colsB);
}

int test() {
    char transA = 'N', transB = 'N';
    double one = 1.0, zero = 0.0;

//    F77_dgemm(&transA, &transB,
//            &rowsA, &colsB, &common, &one,
//            A, &rowsA,
//            B, &common, &zero,
//            C, &rowsA);

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
            rowsA, colsB, rowsA, one,
            A, 1024,
            B, 1024, zero,
            C, 1024);

    printf("%f\n", *C);

    return 0;
}

int main(int argc, char * argv[]) {
    create_matices();

    for(int i = 0; i < 50; i++) {
        test();
    }

    return 0;
}

