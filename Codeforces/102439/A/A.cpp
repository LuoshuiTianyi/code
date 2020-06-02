#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define LD long double
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
LL read() {
  char ch = getchar();
  int fl = 0;
  LL x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  return fl ? -x : x;
}
void rstr(char *s) {
  char *x = s;
  char ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
  while (ch != ' ' && ch != '\n' && ch != '\r') {
    *x++ = ch;
    ch = getchar();
  }
}

const int Max_n = 1e5 + 5;
const LD eps = 1e-8;
int n, id[Max_n];
LD a, b;
struct light {
  LD x, v;
} k[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), a = read(), b = read();
  for (int i = 1; i <= n; i++)
    k[i].x = read(), k[i].v = read();
}
}  // namespace Input

bool pd(LD v0, LD v, LD d) {
  return sqrt(v0 * v0 - 2.0 * b * d);
}

namespace Init {
bool cmp(light a, light b) { return a.x < b.x; }
int top, stk[Max_n];
void main() {
  for (int i = 1; i <= n; i++) {
    while (top && pd(k[stk[top]].v, k[i].v, k[i].x - k[stk[top]].x)) top--;
    stk[++top] = i;
  }
}
}  // namespace Init

namespace Solve {
LD v[Max_n];
bool check(LD t, LD v0, LD lim, LD d) {
  
}
void main() {
  for (int i = 0; i < top; i++) {
    light x = k[stk[i]], y = k[stk[i + 1]];
    LD v0 = v[i], d = y.x - x.x, v1 = y.v;
    LD l = 0, r = 1e4, ans;
    while (r - l > eps) {
      LD mid = (l + r) / 2;
      if (check(mid, v0, v1, d)) l = ans = mid;
      else r = mid;
    }
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
