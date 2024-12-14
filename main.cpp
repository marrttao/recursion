#include <iostream>
using namespace std;

//recursion func

void stars_in_row(int n) {
	if (n == 0) {
		return;
	}
	cout << "*";
	stars_in_row(n - 1);
}

int main() {
	int* n = new int;
	cin >> *n;
	stars_in_row(*n);

	delete n;
	return 0;
}