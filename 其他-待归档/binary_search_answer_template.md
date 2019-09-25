# 二分答案
 - v1.2
 - require: C++98
 - [ ] 封装


整数内二分答案，注意右边界需要扩展一位。
```C++
#include <iostream>
#include <string>
using namespace std;
int check(int x, int array[]) { return array[x]; }
int main() {
    int a[11][10];
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < i; j++)
            a[i][j] = 0;
        for (int j = i; j < 10; j++)
            a[i][j] = 1;
    }
    for (int i = 0; i < 11; i++) {
        int l = 0, r = 9;
        for (; l <= r;) {
            int mid = (l + r) / 2;
            if (check(mid, a[i]))
                r = mid - 1;
            else
                l = mid + 1;
        }

        // show result
        cout << "====================\n";
        for (int j = 0; j < 10; j++)
            cout << a[i][j] << " ";
        cout << endl;
        string pointer, labelL, labelR;
        pointer = "                      ";
        labelL = "                      ";
        labelR = "                      ";
        if (l >= 0) {
            pointer[l * 2] = '^';
            labelL[l * 2] = 'l';
        }
        if (r >= 0) {
            pointer[r * 2] = '^';
            labelR[r * 2] = 'r';
        }
        cout << pointer << endl;
        cout << labelL << endl;
        cout << labelR << endl;
        cout << l << "," << r << endl;
    }
    return 0;
}
```