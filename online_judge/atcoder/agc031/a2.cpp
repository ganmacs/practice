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

const int L = 1e9 + 7;

int main()
{
  int N;
  string S;
  map<char, long long> M;
  cin >> N >> S;

  for (auto& vi: S) {
    M[vi]++;
  }

  long long ans = 1;
  for (auto& vi: M) {
    ans *= (vi.second + 1);
    ans %= L;
  }

  cout << max((long long)1, (ans-1) % L) << endl;
  return 0;
}
