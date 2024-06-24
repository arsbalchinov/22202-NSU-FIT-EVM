#include <iostream>
#include <random>
#include <fstream>
#include <intrin.h>
#include <limits.h>
using namespace std;

void directArrayFill(int *array, const int len) {
    for (int i = 0; i < len - 1; i++) {
        array[i] = i + 1;
    }
    array[len - 1] = 0;
}

void reverseArrayFill(int *array, const int len) {
    for (int i = len - 1; i > 0; i--) {
        array[i] = i - 1;
    }
    array[0] = len - 1;
}

void randomArrayFill(int *array, const int len) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(0,len - 1);
    memset(array, -1, sizeof(int) * len);
    int tmp;
    while ((tmp = dist(rng)) == 0) {
        continue;
    }
    array[0] = tmp;
    int next = tmp;
    for (int i = 0; i < len - 2; i++) {
        tmp = dist(rng);
        for (int j = 0; j < len; j++) {
            const int ind = (tmp + j) % len;
            if (array[ind] == -1 && next != ind) {
                array[next] = ind;
                tmp = ind;
                break;
            }
        }
        next = tmp;
    }
    array[next] = 0;
}

void arrayTraversal(const int *array, const int len, const int numberOfTraversals) {
    for (int k = 0, i = 0; i < len * numberOfTraversals; i++) {
        k = array[k];
    }
}

int main() {
    const int nMin = 256; //2^8 - 1кб
    const int nMax = 256 * 1024 * 32; //2^23 - 32мб
    ofstream file("data.txt");
    int *array = new int[nMax];
    const int k = 100;
    for (int n = nMin; n <= nMax; n *= 2) {
        unsigned long long start = 0, end = 0;

        directArrayFill(array, n);
        unsigned long long t = LONG_LONG_MAX;
        for (int j = 0; j < 1; j++) {
            arrayTraversal(array, n, 1); // прогрев кэша
            start = __rdtsc();
            arrayTraversal(array, n, k);
            end = __rdtsc();
            t = min(t, end - start);
        }
        file << "N = " << n/256 << " KB. Direct traversal: " << (t)/(k * n) << " CPU cycles\n";

        reverseArrayFill(array, n);
        t = LONG_LONG_MAX;
        for (int j = 0; j < 1; j++) {
            arrayTraversal(array, n, 1); // прогрев кэша
            start = __rdtsc();
            arrayTraversal(array, n, k);
            end = __rdtsc();
            t = min(t, end - start);
        }
        file << "N = " << n/256 << " KB. Reverse traversal: " << (t)/(k * n) << " CPU cycles\n";

        randomArrayFill(array, n);
        t = LONG_LONG_MAX;
        for (int j = 0; j < 1; j++) {
            arrayTraversal(array, n, 1); // прогрев кэша
            start = __rdtsc();
            arrayTraversal(array, n, k);
            end = __rdtsc();
            t = min(t, end - start);
        }
        file << "N = " << n/256 << " KB. Random traversal: " << (t)/(k * n) << " CPU cycles\n";
    }
    delete[] array;
}
