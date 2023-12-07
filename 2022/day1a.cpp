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

  int ret = 0;
  int tsum = 0;
  string tmp;
  char cc[1000];
  while (cin.getline(cc, 1000)) {
    tmp = string(cc);
    if (tmp != "") {
      tsum += stoi(tmp);
    } else {
      ret = max(ret, tsum);
      tsum = 0;
    }
  }
  ret = max(ret, tsum);

  cout << ret << endl;

  return 0;
}

