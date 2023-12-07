#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif

#define _CRT_SECURE_NO_WARNINGS
#define LOCAL

using namespace std;


int main(int argc, char* argv[])
{
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  string line;
  int sum = 0;
  while (cin >> line) {
    cout << line << endl;
    int d1 = -1, d2 = -1;
    for(int ic = 0; ic < line.size(); ++ic) {
      char c = line[ic];
      if (c >= '1' && c <= '9') {
        if (d1 == -1)
          d1 = c - '0';
        d2 = c - '0';
      }
    }
    sum += d1 * 10 + d2;
  }

  cout << sum << endl;

  return 0;
}

