#include <iostream>
using namespace std;

int rec_pow(int n, int m)
{
    if (m == 0)
        return 1;
    return n * rec_pow(n, m - 1);
}

int main()
{
    int res = rec_pow(2, 3);
    cout << res << endl;
    return 0;
}