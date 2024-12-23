#include <iostream>
#include <random>
#include <type_traits>
#include <limits>

using namespace std;

template<typename T>
void check_type(mt19937& gen, T& dis) {
    if constexpr (is_same<T, uniform_int_distribution<int>>::value) {
        dis.param(typename uniform_int_distribution<int>::param_type(1, 100));
    }
    else if constexpr (is_same<T, uniform_real_distribution<float>>::value) {
        dis.param(typename uniform_real_distribution<float>::param_type(1.0, 100.0));
    }
    else if constexpr (is_same<T, uniform_real_distribution<double>>::value) {
        dis.param(typename uniform_real_distribution<double>::param_type(1.0, 100.0));
    }
}

template<typename T>
T* fill_arr(int size) {
    random_device rd;
    mt19937 gen(rd());
    typename conditional<is_same<T, int>::value, uniform_int_distribution<int>,
        typename conditional<is_same<T, float>::value, uniform_real_distribution<float>,
        typename conditional<is_same<T, double>::value, uniform_real_distribution<double>,
        uniform_int_distribution<int>>::type>::type>::type dis;
    check_type(gen, dis);
    T* arr = new T[size];
    for (int i = 0; i < size; i++) {
        if constexpr (is_same<T, char>::value) {
            arr[i] = static_cast<char>(dis(gen) % 26 + 'a');
        }
        else {
            arr[i] = dis(gen);
        }
    }
    return arr;
}

template<typename T>
T** fill_two_dimensional_arr(int size) {
    random_device rd;
    mt19937 gen(rd());
    typename conditional<is_same<T, int>::value, uniform_int_distribution<int>,
        typename conditional<is_same<T, float>::value, uniform_real_distribution<float>,
        typename conditional<is_same<T, double>::value, uniform_real_distribution<double>,
        uniform_int_distribution<int>>::type>::type>::type dis;
    check_type(gen, dis);
    T** two_dimensional_arr = new T * [size];
    for (int i = 0; i < size; i++) {
        two_dimensional_arr[i] = new T[size];
        for (int j = 0; j < size; j++) {
            if constexpr (is_same<T, char>::value) {
                two_dimensional_arr[i][j] = static_cast<char>(dis(gen) % 26 + 'a');
            }
            else {
                two_dimensional_arr[i][j] = dis(gen);
            }
        }
    }
    return two_dimensional_arr;
}

template<typename T>
T*** fill_three_dimensional_arr(int size) {
    random_device rd;
    mt19937 gen(rd());
    typename conditional<is_same<T, int>::value, uniform_int_distribution<int>,
        typename conditional<is_same<T, float>::value, uniform_real_distribution<float>,
        typename conditional<is_same<T, double>::value, uniform_real_distribution<double>,
        uniform_int_distribution<int>>::type>::type>::type dis;
    check_type(gen, dis);
    T*** three_dimensional_arr = new T * *[size];
    for (int i = 0; i < size; i++) {
        three_dimensional_arr[i] = new T * [size];
        for (int j = 0; j < size; j++) {
            three_dimensional_arr[i][j] = new T[size];
            for (int k = 0; k < size; k++) {
                if constexpr (is_same<T, char>::value) {
                    three_dimensional_arr[i][j][k] = static_cast<char>(dis(gen) % 26 + 'a');
                }
                else {
                    three_dimensional_arr[i][j][k] = dis(gen);
                }
            }
        }
    }
    return three_dimensional_arr;
}

template<typename T>
void delete_two_dimensional_arr(T** arr, int size) {
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

template<typename T>
void delete_three_dimensional_arr(T*** arr, int layers, int size) {
    for (int i = 0; i < layers; i++) {
        for (int j = 0; j < size; j++) {
            delete[] arr[i][j];
        }
        delete[] arr[i];
    }
    delete[] arr;
}

template<typename T>
T max_in_arr(T* arr, int size, int index = 0, T max = std::numeric_limits<T>::min()) {
    if (arr[index] > max) {
        max = arr[index];
    }
    if (index == size - 1) {
        return max;
    }
    return max_in_arr(arr, size, index + 1, max);
}

template<typename T>
T max_in_two_dimensional_arr(T** two_dimensional_arr, int size, int index_rows = 0, int index_cols = 0, T max = std::numeric_limits<T>::min()) {
    if (two_dimensional_arr[index_rows][index_cols] > max) {
        max = two_dimensional_arr[index_rows][index_cols];
    }
    if (index_cols == size - 1 && index_rows == size - 1) {
        return max;
    }
    if (index_rows == size - 1) {
        return max_in_two_dimensional_arr(two_dimensional_arr, size, 0, index_cols + 1, max);
    }
    return max_in_two_dimensional_arr(two_dimensional_arr, size, index_rows + 1, index_cols, max);
}

template<typename T>
T max_in_three_dimensional_arr(T*** three_dimensional_arr, int size_one, int size_two, int size_three, int index_one = 0, int index_two = 0, int index_three = 0, T max = std::numeric_limits<T>::min()) {
    if (three_dimensional_arr[index_one][index_two][index_three] > max) {
        max = three_dimensional_arr[index_one][index_two][index_three];
    }
    if (index_one == size_one - 1 && index_two == size_two - 1 && index_three == size_three - 1) {
        return max;
    }
    if (index_three < size_three - 1) {
        return max_in_three_dimensional_arr(three_dimensional_arr, size_one, size_two, size_three, index_one, index_two, index_three + 1, max);
    }
    if (index_two < size_two - 1) {
        return max_in_three_dimensional_arr(three_dimensional_arr, size_one, size_two, size_three, index_one, index_two + 1, 0, max);
    }
    if (index_one < size_one - 1) {
        return max_in_three_dimensional_arr(three_dimensional_arr, size_one, size_two, size_three, index_one + 1, 0, 0, max);
    }
    return max;
}

template<typename T>
T max_of_two(T a, T b) {
    return (a > b) ? a : b;
}

template<typename T>
T max_of_three(T a, T b, T c) {
    T max_ab = (a > b) ? a : b;
    return (max_ab > c) ? max_ab : c;
}

int main() {
    int size_arr;
    cout << "Size of arr: ";
    cin >> size_arr;
    float* arr = fill_arr<float>(size_arr);
    int size_two_dim_arr;
    cout << "Size of two-dimensional arr: ";
    cin >> size_two_dim_arr;
    char** two_dimensional_arr = fill_two_dimensional_arr<char>(size_two_dim_arr);
    int size_three_dim_arr;
    cout << "Size of three-dimensional arr: ";
    cin >> size_three_dim_arr;
    int*** three_dimensional_arr = fill_three_dimensional_arr<int>(size_three_dim_arr);

    cout << "One-dimensional array:" << endl;
    for (int i = 0; i < size_arr; i++) {
        cout << arr[i] << " ";
    }
    cout << endl << endl;

    cout << "Two-dimensional array:" << endl;
    for (int i = 0; i < size_two_dim_arr; i++) {
        for (int j = 0; j < size_two_dim_arr; j++) {
            cout << two_dimensional_arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Three-dimensional array:" << endl;
    for (int i = 0; i < size_three_dim_arr; i++) {
        cout << "Layer " << i + 1 << ":" << endl;
        for (int j = 0; j < size_three_dim_arr; j++) {
            for (int k = 0; k < size_three_dim_arr; k++) {
                cout << three_dimensional_arr[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    cout << "Max in arr: " << max_in_arr(arr, size_arr) << endl;
    cout << "Max in two-dimensional arr: " << max_in_two_dimensional_arr(two_dimensional_arr, size_two_dim_arr) << endl;
    cout << "Max in three-dimensional arr: " << max_in_three_dimensional_arr(three_dimensional_arr, size_three_dim_arr, size_three_dim_arr, size_three_dim_arr) << endl;

    int a, b, c;
    cout << "Enter a: ";
    cin >> a;
    cout << "Enter b: ";
    cin >> b;
    cout << "Enter c: ";
    cin >> c;
    cout << "Max of a and b: " << max_of_two(a, b) << endl;
    cout << "Max of a, b and c: " << max_of_three(a, b, c) << endl;

    delete[] arr;
    delete_two_dimensional_arr(two_dimensional_arr, size_two_dim_arr);
    delete_three_dimensional_arr(three_dimensional_arr, size_three_dim_arr, size_three_dim_arr);

    return 0;
}
