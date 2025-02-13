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

int main(int argc, char *argv[])
{
  int N, K;
  cin >> N >> K;
  vector<unsigned long long> V(N);
  unsigned long long ans = 0;

  for (int i = 0; i < N; i++) {
    cin >> V[i];
  };

  for (int i = 0; i < (N - K + 1); i++) {
    for (int j = 0; j < K; j++) {
      ans += V[i + j];
    }
  }

  cout << ans << endl;
  return 0;
}
