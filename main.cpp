#include <iostream>
using namespace std;

int sum_of_range(int a, int b, int sum = 0) {
	if (b < a) {
		return sum;
	}
	return sum_of_range(a, b - 1, sum + b);
}

int main() {
	cout << sum_of_range(1, 10);
	return 0;
}	
