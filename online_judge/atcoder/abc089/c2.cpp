#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

string SSS[10] = { "MAR", "MAC", "MAH", "MRC", "MRH", "MCH", "ARC", "ARH", "ACH", "RCH" };

int main()
{
  int N;
  cin >> N;
  map<char, int> M;
  string S;
  for (int i = 0; i < N; i++) {
    cin >> S;
    M[S[0]]++;
  }

  long long ans = 0;
  for (auto& vii: SSS) {
    long long t = 1;
    for (auto& vi: vii) {
      t *= M[vi];
    }

    ans += t;
  }
  cout << ans << endl;
  return 0;
}
