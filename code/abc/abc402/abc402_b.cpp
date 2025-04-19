#include<bits/stdc++.h>

using namespace std;

int main(void) {
  int q;
  cin >> q;
  queue<int> que;
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int x;
      cin >> x;
      que.emplace(x);
    } else {
      cout << que.front() << endl;
      que.pop();
    }
  }
}