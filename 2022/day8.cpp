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

  int ret = 0;
  int max_scenic = 0;
  for(int r = 0; r < input.size(); ++r) {
    for(int c = 0; c < input[r].size(); ++c) {
      if (r == 0 || r == input.size()) {
        ret++;
        continue;
      }
      if (c == 0 || c == input[r].size()) {
        ret++;
        continue;
      }
      bool allshort = true;
      int scenic_score = 1;
      int shortdirs = 0;
      int tsum = 0;
      for(int rr = r-1; rr >= 0; --rr) {
        tsum++;
        allshort &= (input[rr][c] < input[r][c]);
        if (input[rr][c] >= input[r][c]) {
          break;
        }
      }
      shortdirs += allshort;
      scenic_score *= tsum;

      tsum = 0;
      allshort = true;
      for(int rr = r+1; rr < input.size(); ++rr) {
        tsum++;
        allshort &= (input[rr][c] < input[r][c]);
        if (input[rr][c] >= input[r][c]) {
          break;
        }
      }
      shortdirs += allshort;
      scenic_score *= tsum;

      tsum = 0;
      allshort = true;
      for(int cc = c-1; cc >= 0; --cc) {
        tsum++;
        allshort &= (input[r][cc] < input[r][c]);
        if (input[r][cc] >= input[r][c]) {
          break;
        }
      }
      shortdirs += allshort;
      scenic_score *= tsum;

      tsum = 0;
      allshort = true;
      for(int cc = c+1; cc < input[r].size(); ++cc) {
        tsum++;
        allshort &= (input[r][cc] < input[r][c]);
        if (input[r][cc] >= input[r][c]) {
          break;
        }
      }
      shortdirs += allshort;
      scenic_score *= tsum;

      if (shortdirs > 0)
        ret++;

      max_scenic = max(max_scenic, scenic_score);
    }
  }

  cout << "Part A: " << ret << endl;
  cout << "Part B: " << max_scenic << endl;

  return 0;
}

