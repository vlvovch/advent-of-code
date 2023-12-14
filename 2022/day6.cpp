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

  string input;
  cin >> input;
  for(int i = 3; i < input.size(); ++i) {
    bool fl = true;
    for(int j = 0; j < 4; ++j) 
      for(int jj = j+1; jj < 4; ++jj)
        fl &= (input[i-j] != input[i-jj]);
    if (fl) {
      cout << "Part A: " << i + 1 << endl;
      break;
    }
  }

  for(int i = 13; i < input.size(); ++i) {
    bool fl = true;
    for(int j = 0; j < 14; ++j) 
      for(int jj = j+1; jj < 14; ++jj)
        fl &= (input[i-j] != input[i-jj]);
    if (fl) {
      cout << "Part B: " << i + 1 << endl;
      break;
    }
  }

  

  return 0;
}

