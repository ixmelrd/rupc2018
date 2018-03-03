#include <iostream>
#include <map>
using namespace std;

int i;
int n;
int a[100000];
int ans[100000];
int c;
int acc;
map<int, int> m;

int main() {
  scanf("%d", &n);
  for (i = 0; i < n; i++) scanf("%d", a + i);
  for (i = 0; i < n; i++) {
    m[a[i]]++;
    m[a[n - 1 - i]]--;
    acc = 0;
    for (auto &p : m) acc |= p.second;
    if (acc == 0) ans[c++] = i + 1;
  }
  printf("%d", ans[0]);
  for (i = 1; i < c; i++) printf(" %d", ans[i]);
  printf("\n");
}
