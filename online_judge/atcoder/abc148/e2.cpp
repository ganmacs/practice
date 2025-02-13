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
  long long N;
  cin >> N;

  if (N % 2 == 1) {
    cout << 0 << endl;
    return 0;
  }
  long long ans = 0;
  while (N) {
    ans += N / 5 / 2;
    N /= 5;
  }

  cout << ans << endl;
  return 0;
}
