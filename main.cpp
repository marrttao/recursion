#include <iostream>
#include <random>
using namespace std;



int sum(int* arr, int index, int range) {
    if (index == range) {
        return 0;
    }
    return arr[index] + sum(arr, index + 1, range);
}



void result(int* arr, int index, int& minSum, int& minIndex, bool firstCall) {
    if (firstCall) {
        minSum = 1000000;
        minIndex = 0;
    }
    if (index > 90) {
        return;
    }
    int currentSum = sum(arr, index, index + 10);

    if (currentSum < minSum) {
        minSum = currentSum;
        minIndex = index;
    }
    result(arr, index + 1, minSum, minIndex, false);
}



int* start_random_array(int size = 100) {

	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(1, 100);

    int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		arr[i] = dist(mt);
	}
    return arr;
}

int main() {
    int* arr = start_random_array();
    for (int i = 0; i < 100; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int minSum, minIndex;

    result(arr, 0, minSum, minIndex, true);

    cout << "Min sum: " << minSum << endl;
    cout << "Index : " << minIndex << endl;

    delete[] arr;
    return 0;
}
