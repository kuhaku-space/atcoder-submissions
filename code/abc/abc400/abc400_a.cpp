#include <iostream>
using namespace std;
int main(void){
	int a;
	cin >> a;
	if (400 % a == 0) {
		cout << 400 / a << endl;
	} else {
		cout << -1 << endl;
	}
}
