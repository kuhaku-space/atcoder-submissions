#include<bits/stdc++.h>

using namespace std;

int main(void) {
  string s;
  cin >> s;
  string ans;
  for (auto c : s) {
    if (isupper(c)) ans += c;
  }
  cout << ans;
}