#include <algorithm>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <map>

using namespace std;

static const int N = 4;
static const int dy[4] = {-1, 0, 0, 1};
static const int dx[4] = {0, -1, 1, 0};

struct m_t {
  int m[N][N];
  int x0, y0;
  int md;
  int cost;

  bool operator < (const m_t &oth) const {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (oth.m[i][j] == m[i][j]) continue;
        return m[i][j] > oth.m[i][j];
      }
    }
    return false;
  }
};

struct state {
  m_t mt;
  int ev;

  bool operator < (const state &oth) const { return ev > oth.ev; }
};

map<m_t, bool> M;
priority_queue<state> Q;
int MD[16][N][N];

int amd(m_t m)
{
  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (m.m[i][j] == 0) continue;
      ans += MD[m.m[i][j]-1][i][j];
    }
  }
  return ans;
}

int bfs(m_t mm)
{
  int xx, yy;
  m_t m, tmp;
  state init, news, s;

  mm.cost = 0;
  mm.md = amd(mm);

  init.mt = mm;
  init.ev = mm.md + mm.cost;
  Q.push(init);

  while (!Q.empty()) {
    s = Q.top(); Q.pop();
    m = s.mt;
    if (m.md == 0) return m.cost;
    M[m] = true;

    for (int i = 0; i < 4; i++) {
      yy = dy[i] + m.y0;
      xx = dx[i] + m.x0;
      if (!(0 <= xx && xx < N && 0 <= yy && yy < N)) continue;
      tmp = m;

      tmp.md -= MD[tmp.m[yy][xx]-1][yy][xx];
      tmp.md += MD[tmp.m[yy][xx]-1][m.y0][m.x0];

      swap(tmp.m[yy][xx], tmp.m[m.y0][m.x0]);

      if (!M[tmp]) {
        tmp.y0 = yy;
        tmp.x0 = xx;
        tmp.cost++;

        news.mt = tmp;
        news.ev = tmp.cost + tmp.md;
        Q.push(news);
      }
    }
  }
  return -1;
}

int main(){
  m_t m;
  int v, x, y;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> v;
      if (v == 0) {
        m.y0 = i; m.x0 = j;
      }
      m.m[i][j] = v;
    }
  }

  for (int i = 0; i < 16; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        y = i / N;
        x = i % N;
        MD[i][j][k] = abs(y-j) + abs(x-k);
      }
    }
  }

  cout << bfs(m) << endl;;
}
