#include <iostream>
using namespace std;

int biggest_common_divider(int a, int b, int divider = 1) {
	if (a % divider == 0 && b % divider == 0) {
		if (divider == a || divider == b) {
			return divider;
		}
		return biggest_common_divider(a, b, divider + 1);
	}
	return biggest_common_divider(a, b, divider + 1);

}

int main() {
	int a, b;
	cout << "Enter two numbers: ";
	cin >> a >> b;
	cout << "Divider: " << biggest_common_divider(a, b) << endl;
	return 0;
}