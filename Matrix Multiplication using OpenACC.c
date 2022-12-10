// Matrix multiplication using OpenACC

#include <stdio.h>
#include <stdlib.h>

#define N 1000

// Matrix data type
typedef struct {
  float *data;
  int rows;
  int cols;
} Matrix;

// Allocate memory for a matrix
Matrix allocate_matrix(int rows, int cols) {
  Matrix mat;
  mat.data = (float*)malloc(sizeof(float) * rows * cols);
  mat.rows = rows;
  mat.cols = cols;
  return mat;
}

// Free memory for a matrix
void free_matrix(Matrix mat) {
  free(mat.data);
}

// Initialize a matrix with random values
void init_matrix(Matrix mat) {
  for (int i = 0; i < mat.rows * mat.cols; i++) {
    mat.data[i] = rand() / (float)RAND_MAX;
  }
}

// Serial matrix multiplication
Matrix multiply_matrix(Matrix mat1, Matrix mat2) {
  Matrix result = allocate_matrix(mat1.rows, mat2.cols);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.cols; j++) {
      float sum = 0;
      for (int k = 0; k < mat1.cols; k++) {
        sum += mat1.data[i * mat1.cols + k] * mat2.data[k * mat2.cols + j];
      }
      result.data[i * result.cols + j] = sum;
    }
  }

  return result;
}

// Parallel matrix multiplication using OpenACC
Matrix multiply_matrix_parallel(Matrix mat1, Matrix mat2) {
  Matrix result = allocate_matrix(mat1.rows, mat2.cols);

  #pragma acc data copyin(mat1.data[0:mat1.rows*mat1.cols], mat2.data[0:mat2.rows*mat2.cols]) copyout(result.data[0:result.rows*result.cols])
  {
    #
