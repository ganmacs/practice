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

  int N, a[2][123];
  cin >> N;

  a[1][0] = a[0][0] = 0;

  for (int i = 1; i <= N; i++) {
    cin >> a[0][i];
    a[0][i] += a[0][i-1];
  }

  for (int i = 1; i <= N; i++) {
    cin >> a[1][i];
    a[1][i] += max(a[0][i], a[1][i-1]);
  }

  printf("%d\n", a[1][N]);
}
