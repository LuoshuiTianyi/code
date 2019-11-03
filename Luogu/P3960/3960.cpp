#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}

const int Max_n = 3e5 + 5, LIM = 1 << 20;
int n, m, Q;
int x[Max_n], y[Max_n];
LL q[Max_n << 1];
bool qt[Max_n << 1];
vector<int> que[Max_n], pad[Max_n];

struct Tree {
  int t1, t2, add[Max_n], del[Max_n];
  int c[LIM + 1];
  #define mid (l + r >> 1)
  #define ls (o - (o & -o >> 1))
  #define rs (o + (o & -o >> 1))
  void Init() {
    for (int p = 1; p <= m; p++)
      for (int i = p; i <= LIM; i += i & -i) c[i] = 1;
  }
  void Add(int k, int x) {
    if (x > 0)
      add[++t1] = k;
    else
      del[++t2] = k;
    for (int i = k; i <= LIM; i += i & -i) c[i] += x;
  }
  void find(int k) {
    int l = 1, r = LIM, o = LIM >> 1;
    while (l < r) {
      if (c[o] >= k) o = ls, r = mid;
      else k -= c[i], o = rs, l = mid + 1;
    }
    return l;
  }
  void init() {
    while (t1) Add(add[--t1], -1);
    while (t2) Add(del[--t2], 1);
  }
} s;

namespace Input {
void main() {
  n = read(), m = read(), Q = read();
  for (int i = 1; i <= Q; i++) x[i] = read(), y[i] = read();
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= n; i++) q[i] = 1ll * i * m, s.add(i, 1);
  for (int i = 1; i <= Q; i++) {
    que[x[i]].push_back(i);
  }
  s.init(), s.Init();
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifdef Thyu
  freopen("3960.in", "r", stdin);
  freopen("3960.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
