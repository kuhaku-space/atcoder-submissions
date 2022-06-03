#include <bits/stdc++.h>
using namespace std;
int main() {
    int X;
    int A;
    int B;
    int C;
    int D;
    cin >> X;
    int i = 0;
    for (i = 0; i < 10; i++) {
        if (i <= (X / 1000) && (X / 1000) < i + 1) {
            A = i;
        }
    }
    for (i = 0; i < 10; i++) {
        if (i <= ((X - A * 1000) / 100) && ((X - A * 10000) / 100) < i + 1) {
            B = i;
        }
    }
    for (i = 0; i < 10; i++) {
        if (i <= ((X - A * 1000 - B * 100) / 10) && ((X - A * 1000 - B * 100) / 10) < i + 1) {
            C = i;
        }
    }
    for (i = 0; i < 10; i++) {
        if (i <= ((X - A * 1000 - B * 100 - C * 10) / 1) && ((X - A * 1000 - B * 100 - C * 10) / 1) < i + 1) {
            D = i;
        }
    }
    // cout << A << B << C << D << endl;
    if ((A == B) && (B == C) && (C == D)) {
        cout << "Weak" << endl;
    } else if ((B == A + 1 || B == A - 9) && (C == B + 1 || C == B - 9) && (D == C + 1 || D == C - 9)) {
        cout << "Weak" << endl;
    } else {
        cout << "Strong" << endl;
    }
}
