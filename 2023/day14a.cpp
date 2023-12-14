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
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif


  vector<string> input;
  string s;
  while(cin >> s) {
    input.push_back(s);
  }

  // Tilt north
  for(int c = 0; c < input[0].size(); ++c) {
    for(int r = 0; r < input.size(); ++r) {
      if (input[r][c] == 'O') {
        int rr = r - 1;
        while (rr >= 0 && input[rr][c] == '.') {
          input[rr][c] = 'O';
          input[rr+1][c] = '.';
          --rr;
        }
      }
    }
  }

  for(auto& s: input) {
    cout << s << endl;
  }

  int ret = 0;
  for(int r = 0; r < input.size(); ++r) {
    for(int c = 0; c < input[r].size(); ++c) {
      if (input[r][c] == 'O') {
        ret += input.size() - r;
      }
    }
  }

  // Output
  cout << ret << endl;

  return 0;
}

