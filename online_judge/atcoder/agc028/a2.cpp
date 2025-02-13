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
#include <numeric>

using namespace std;

int main()
{
  long long N, M;
  cin >> N >> M;
  long long L = lcm(N, M);
  long long g = gcd(N, M);
  string S, T;
  cin >> S >> T;

  for (int i = 0; i < g ; i++) {
    if (S[(N*i)/g] != T[(M*i)/g]) {
      printf("%d\n", -1);
      return 0;
    }
  }

  printf("%lld\n", L);
  return 0;
}
