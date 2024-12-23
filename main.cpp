#include <iostream>
#include <random>
using namespace std;

void create_matrix(int**& matrix, int rows, int cols) {
	matrix = new int* [rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
	}
}
void print_matrix(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void fill_matrix(int** matrix, int rows, int cols) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, 100);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = dis(gen);
		}
	}
}

int min_in_main_diagonal(int** matrix, int rows, int cols, int i = 0) {
	
	if (i == rows || i == cols) {
		return matrix[i - 1][i - 1]; 
	}

	int min = min_in_main_diagonal(matrix, rows, cols, i + 1);

	if (matrix[i][i] < min) {
		return matrix[i][i];
	}

	return min;
}


void sort_matrix_for_rows(int** matrix, int rows, int cols) {
	int temp;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols - 1; j++) {
			for (int k = 0; k < cols - j - 1; k++) {
				if (matrix[i][k] > matrix[i][k + 1]) {
					temp = matrix[i][k];
					matrix[i][k] = matrix[i][k + 1];
					matrix[i][k + 1] = temp;
				}
			}
		}
	}
}

void delete_matrix(int**& matrix, int rows) {
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = nullptr;
}


int main() {
	int** matrix;
	int rows, cols;
	cout << "rows: ";
	cin >> rows;
	cout << "cols: ";
	cin >> cols;
	create_matrix(matrix, rows, cols);

	//cout matrix
	fill_matrix(matrix, rows, cols);
	print_matrix(matrix, rows, cols);
	min_in_main_diagonal(matrix, rows, cols);

	cout << endl << "min: " << min_in_main_diagonal(matrix, rows, cols) << endl;
	cout << "Sorted matrix: " << endl;
	print_matrix(matrix, rows, cols);

	delete_matrix(matrix, rows);

	return 0;
}