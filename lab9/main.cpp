#include <iostream>
#include <fstream>
#include <intrin.h>
using namespace std;

//Заполнение массива.
void fillArray(int* array, int numbOfBanks, int fragmentSize, int offset) {
    for (int i = 0; i < numbOfBanks-1; i++) {
        for (int j = 0; j < fragmentSize; j++) {
            array[offset * i + j] = offset * (i+1) + j;
        }
    }
    for (int j = 0; j < fragmentSize-1; j++) {
        array[offset * (numbOfBanks-1) + j] = j+1;
    }
    array[offset * (numbOfBanks-1) + fragmentSize-1] = 0;
}
//Обход массива.
void arrayTraversal(const int *array, const int len, const int amount) {
    for (int k = 0, i = 0; i < len * amount; i++) {
        k = array[k];
    }
}

//Size – объем кэшпамяти, N – число фрагментов, Offset – смещение между началами соседних фрагментов.
int main() {
    int arraySize = 256 * 1024 * 16 * 32;
    int size = 256 * 64; //64 кб: L1 
    int offset = 256 * 1024 * 8;
    int* array = new int[arraySize];
    ofstream file("data.txt");
    for (int n = 1; n <= 32; n++) {
        fillArray(array, n, size/n, offset);
        unsigned long long t = LONG_LONG_MAX;
        for (int i = 0; i < 30; i++) {
            arrayTraversal(array, size, 1);
            unsigned long long start = __rdtsc();
            arrayTraversal(array, size, 10);
            unsigned long long end = __rdtsc();
            t = min(end - start, t);
        }
        file << n << ", " << t / 10 / size << endl;
    }
    delete[] array;
}
