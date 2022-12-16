// Matrix Multiplication using OpenACC

#include <stdio.h>
#include <openacc.h>

void matrix_multiply(float *a, float *b, float *c, int m, int n, int p) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            c[i*p + j] = 0.0f;
            for (int k = 0; k < n; k++) {
                c[i*p + j] += a[i*n + k] * b[k*p + j];
            }
        }
    }
}

int main() {
    const int M = 1000, N = 1000, P = 1000;
    float a[M*N], b[N*P], c[M*P];

    // Initialize arrays
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            a[i*N + j] = (float)i*j;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < P; j++) {
            b[i*P + j] = (float)i*j;
        }
    }

    // Accelerate the computation using OpenACC
    #pragma acc data copyin(a[0:M*N], b[0:N*P]), copyout(c[0:M*P])
    {
        #pragma acc parallel loop collapse(2)
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < P; j++) {
                float sum = 0.0f;
                for (int k = 0; k < N; k++) {
                    sum += a[i*N + k] * b[k*P + j];
                }
                c[i*P + j] = sum;
            }
        }
    }

    // Printing the results
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("c[%d][%d] = %f\n", i, j, c[i*P + j]);
        }
    }

    return 0;
}

