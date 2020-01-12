#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
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

const int Max_n = 6e5 + 5, mod = 998244353, G = 3;
int n;

int len, bit, rev[Max_n];
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
}
struct poly {
  int f[Max_n];
  poly() {
    Init();
  }
  void Init() {
    for (int i = 0; i < Max_n; i++) f[i] = 0;
  }
  void dft(int t) {
    for (int i = 0; i < len; i++)
      if (rev[i] > i) swap(f[rev[i]], f[i]);
    for (int l = 1; l < len; l <<= 1) {
      int Wn = ksm(G, (mod - 1) / (l << 1));
      if (t == -1) Wn = ksm(Wn);
      for (int i = 0; i < len; i += l << 1) {
        int Wnk = 1;
        for (int k = i; k < i + l; k++, Wnk = 1ll * Wnk * Wn % mod) {
          int x = f[k], y = 1ll * f[k + l] * Wnk % mod;
          f[k] = (x + y) % mod, f[k + l] = (x - y + mod) % mod;
        }
      }
    }
    if (t == -1)
      for (int i = 0, Inv = ksm(len); i < len; i++) f[i] = 1ll * f[i] * Inv % mod;
  }
  poly dat(int n) {
    poly g;
    for (int i = 0; i < n - 1; i++) g.f[i] = 1ll * (i + 1) * f[i + 1] % mod;
    return g;
  }
  poly itg(int n) {
    poly g;
    for (int i = 1; i < n; i++) g.f[i] = 1ll * f[i - 1] * ksm(i) % mod;
    return g;
  }
  poly inv(int n) {
    static poly g, F;
    g.Init(), F.Init(), g.f[0] = ksm(f[0]);
    for (int deg = 2; deg < (n << 1); deg <<= 1) {
      init(deg * 3);
      for (int i = 0; i < deg; i++) F.f[i] = f[i];
      for (int i = deg; i < len; i++) F.f[i] = 0;
      F.dft(1), g.dft(1);
      for (int i = 0; i < len; i++)
        g.f[i] = (2ll * g.f[i] % mod - 1ll * g.f[i] * g.f[i] % mod * F.f[i] % mod + mod) % mod;
      g.dft(-1);
      for (int i = deg; i < len; i++) g.f[i] = 0;
    }
    return g;
  }
  poly ln(int n) {
    static poly g, df, Inv;
    g.Init(), Inv.Init();
    df = dat(n), Inv = inv(n), init(n * 2);
    df.dft(1), Inv.dft(1);
    for (int i = 0; i < len; i++) g.f[i] = 1ll * df.f[i] * Inv.f[i] % mod;
    g.dft(-1);
    return g.itg(n);
  }
};

poly a, ans;

namespace Input {
void main() {
  n = read();
  for (int i = 0; i < n; i++) a.f[i] = read();
}
}  // namespace Input

namespace Solve {
void main() {
  ans = a.ln(n);
  for (int i = 0; i < n; i++) printf("%d ", ans.f[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4725.in", "r", stdin);
  freopen("4725.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}