#include <cstdio>
#include <ctime>
#include <iostream>
#include <queue>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
struct node {
  int x, y;
};
queue<node> q;
bool bk[201][201];
int p = 5;
int cnt, nx[1000001], ny[1000001];
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "w", stdout);
#endif
  srand(time(NULL)); 
  bk[p][p] = 1;
  for (int i = 1; i <= 1; i++) {
    int x = rand() % 10, y = rand() % 10 + 1;
    bk[x][y] ^= 1, bk[x][y - 1] ^= 1, bk[x + 1][y - 1] ^= 1;
  }
  for (int i = 0; i <= 200; i++)
    for (int j = 0; j <= 200; j++)
      if (bk[i][j])
       cnt++, nx[cnt] = i - p, ny[cnt] = j - p;
  cout << cnt << endl;
  for (int i = 1; i <= cnt; i++)
    cout << nx[i] << " " << ny[i] << endl;
}
