#include <iostream>
#include <chrono>
#include <climits>
#include <intrin.h>
using namespace std;

void mult(float *A, float *B, float *C, const int n) {
    for (int i = 0; i < n; ++i) {
        float *c = C + i * n;
        for (int j = 0; j < n; j += 8) {
            _mm256_storeu_ps(c + j + 0, _mm256_setzero_ps());
        }
        for (int k = 0; k < n; ++k) {
            const float *b = B + k * n;
            __m256 a = _mm256_set1_ps(A[i*n + k]);
            for (int j = 0; j < n; j += 8)
                _mm256_storeu_ps(c + j + 0, _mm256_fmadd_ps(a, _mm256_loadu_ps(b + j + 0), _mm256_loadu_ps(c + j + 0)));
        }
    }
}

void add(const float *A, const float *B, float *C, const int n) {
    for (int i = 0; i < n; i++) {
        const int tmp = i * n;
        for (int j = 0; j < n; j++) {
            C[tmp + j] = A[tmp + j] + B[tmp + j];
        }
    }
}

void sub(const float *A, const float *B, float *C, const int n) {
    for (int i = 0; i < n; i++) {
        const int tmp = i * n;
        for (int j = 0; j < n; j++) {
            C[tmp + j] = A[tmp + j] - B[tmp + j];
        }
    }
}

void transposition(const float *source, float *res, const int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i * n + j] = source[j * n + i];
        }
    }
}

float max1(const float *matrix, const int n) {
    float max1 = INT_MIN;
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < n; j++) {
            sum += matrix[i*n + j];
        }
        max1 = max(sum, max1);
    }
    return max1;
}

float max2(const float *matrix, const int n) {
    float max2 = INT_MIN;
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < n; j++) {
            sum += matrix[j*n + i];
        }
        max2 = max(sum, max2);
    }
    return max2;
}

void div(const float *source, float *res, const float k, const int n) {
    for (int i = 0; i < n; i++) {
        const int tmp = i * n;
        for (int j = 0; j < n; j++) {
            res[tmp + j] = source[tmp + j] / k;
        }
    }
}

void identityMatrixInit(float *matrix, const int n) {
    memset(matrix, 0, sizeof(float) * n * n);
    for (int i = 0; i < n; i++) {
        matrix[i * n + i] = 1;
    }
}

void func(float *source, float *res, const int n, const int m) {
    auto *b = new float[n * n];
    auto *sourceTransp = new float[n * n];
    auto *identityMatrix = new float[n * n];
    auto *r = new float[n * n];
    auto *tmp = new float[n * n];
    transposition(source, sourceTransp, n);
    div(sourceTransp, b, max1(source, n) * max2(source, n), n);
    identityMatrixInit(identityMatrix, n);
    mult(b, source, tmp, n);
    sub(identityMatrix, tmp, r, n);
    memset(res, 0, sizeof(float) * n * n);
    add(res, identityMatrix, res, n);
    add(res, r, res, n);
    float *rPow = tmp;
    tmp = sourceTransp;
    memcpy(rPow, r, sizeof(float) * n * n);
    for (int i = 2; i < m; i++) {
        mult(r, rPow, tmp, n);
        memcpy(rPow, tmp, sizeof(float) * n * n);
        add(res, rPow, res, n);
    }
    mult(res, b, tmp, n);
    memcpy(res, tmp, sizeof(float) * n * n);
    delete[] b;
    delete[] identityMatrix;
    delete[] r;
    delete[] tmp;
    delete rPow;
}

void printMatrix(float *matrix, const int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i * n + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    constexpr int n = 2048;
    auto *a = new float[n * n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                a[i * n + j] = 2;
            }
            else {
                a[i * n + j] = 1;
            }
        }
    }
    auto *aInverted = new float[n * n];
    chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();
    func(a, aInverted, n, 10);
    chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::seconds> (end - begin).count() << "[s]" << endl;
    delete[] a;
    delete[] aInverted;
}
