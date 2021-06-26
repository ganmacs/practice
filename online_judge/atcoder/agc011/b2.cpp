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

int main()
{
  int N, ans = 1;
  cin >> N;
  vector<long long> V(N);
  for (auto& vi: V) cin >> vi;
  sort(V.begin(), V.end());

  vector<long long> VV(N);
  VV[0] = V[0];
  for (int i = 1; i < N; i++) {
    VV[i] = VV[i-1] + V[i];
  }

  for (int i = V.size()-2; i >= 0; i--) {
    if (VV[i]*2 < V[i + 1]) break;
    ans++;
  }

  cout << ans << endl;
  return 0;
}
