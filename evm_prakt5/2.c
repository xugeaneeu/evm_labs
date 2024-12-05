#include <bits/time.h>
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <immintrin.h>
#pragma clang target("avx512f")

#define RAND_FACTOR 10
#define N 2048
#define M 10

#define max(a,b) ((a>b) ? a : b) 

void print(float *matrix) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%f ", matrix[i * N + j]);
    }
    printf("\n");
  }
  puts("");
}

float* make_matrix(void) {
  float *new_matrix = calloc(N*N, sizeof(float));
  if (!new_matrix) return NULL;
  
  for (size_t i = 0; i < N*N; ++i) {
    new_matrix[i] = rand()%RAND_FACTOR;
  }

  return new_matrix;
}

float* make_I_matrix(void) {
  float *I_matrix = calloc(N*N, sizeof(float));
  if (!I_matrix) return NULL;

  for (size_t i = 0; i < N; ++i) {
    I_matrix[i*N + i] = 1.0;
  }

  return I_matrix;
}

float* transpose(float* matrix) {
  float* result = calloc(N*N, sizeof(float));
  if (!result) return NULL;

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0 ; j < N; ++j) {
      result[i*N + j] = matrix[j*N + i];
    }
  }

  return result;
}

float max_sum_row(float *matrix) {
  float max_sum = FLT_MIN;
  for (size_t i = 0; i < N; ++i) {
    float sum = 0;
    for (size_t j = 0; j < N; ++j) {
      sum += fabs(matrix[i*N + j]);
    }
    max_sum = max(sum, max_sum);
  }

  return max_sum;
}

void matrix_scalar_mult(float* matrix, float scalar) {
  __m512 scalar_vec = _mm512_set1_ps(scalar);

  for (size_t i = 0; i < N*N; i += 16) {
    __m512 vec = _mm512_loadu_ps(&matrix[i]);
    __m512 res = _mm512_mul_ps(vec,scalar_vec);
    _mm512_storeu_ps(&matrix[i], res);
  }
}

float* make_B_matrix(float* transposed, float* matrix) {
  float max_row = max_sum_row(matrix);
  float max_column = max_sum_row(transposed);

  matrix_scalar_mult(transposed, 1/(max_row * max_column));
  return transposed;
}

void mult_matrices(float* res, float* mat1, float* mat2) {
  memset(res, 0, N*N*sizeof(float));

  for (size_t i = 0; i < N; ++i) {
    for (size_t k = 0; k < N; ++k) {
      __m512 vec1 = _mm512_set1_ps(mat1[i*N + k]);
      for (size_t j = 0; j < N; j+=16) {
        __m512 vec2 = _mm512_loadu_ps(&mat2[k*N + j]);
        __m512 res_vec = _mm512_loadu_ps(&res[i*N + j]);
        res_vec = _mm512_fmadd_ps(vec1, vec2, res_vec);
        _mm512_storeu_ps(&res[i*N + j], res_vec);
      }
    }
  }
}

void sum_matrices(float* res, float* mat1, float* mat2) {
  for (size_t i = 0; i < N*N; i+=16) {
    __m512 vec1 = _mm512_loadu_ps(&mat1[i]);
    __m512 vec2 = _mm512_loadu_ps(&mat2[i]);
    __m512 res_vec = _mm512_add_ps(vec1, vec2);
    _mm512_storeu_ps(&res[i], res_vec);
  }
}

float* make_R_matrix(float* I, float* B, float* matrix) {
  float* R = calloc(N*N, sizeof(float));
  if (!R) return NULL;
  float* tmp = calloc(N*N, sizeof(float));
  if (!tmp) return NULL;

  mult_matrices(tmp, B, matrix);
  matrix_scalar_mult(tmp, -1);
  sum_matrices(R, I, tmp);

  free(tmp);
  return R;
}

float* find_inverse_matrix(float *matrix) {
  float *result = make_I_matrix();
  float *transposed = transpose(matrix);
  float *I = make_I_matrix();
  float *B = make_B_matrix(transposed, matrix);
  float *R = make_R_matrix(I, B, matrix);

  float* Rn = calloc(N*N, sizeof(float));
  if (!Rn) return NULL;
  memcpy(Rn, R, N*N*sizeof(float));
  float* tmp = calloc(N*N, sizeof(float));
  if (!tmp) return NULL;

  for (size_t i = 0; i < M; ++i) {
    sum_matrices(result, result, Rn);
    mult_matrices(tmp, Rn, R);
    memcpy(Rn, tmp, N*N*sizeof(float));
  }

  mult_matrices(tmp, result, B);
  memcpy(result, tmp, N*N*sizeof(float));

  free(I);
  free(B);
  free(R);
  free(Rn);
  free(tmp);
  return result;
}


int main(void) {
  srand(time(NULL));

  struct timespec start, end;

  float *matrix = make_matrix();
  float *inverse_matrix;

  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  inverse_matrix = find_inverse_matrix(matrix);
  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  printf("Preformance time: %lf sec\n", end.tv_sec - start.tv_sec + 0.000000001*(end.tv_nsec - start.tv_nsec));

  free(matrix);
  free(inverse_matrix);
  return 0;
}
