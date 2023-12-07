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

  vector<string> board;
  string tmp;
  while (cin >> tmp) {
    board.push_back(tmp);
  }

  vector<vector<int>> parts(board.size(), vector<int>(board[0].size(),0));

  auto get_number = [&](int r, int c1, int c2) {
    int ret = 0;
    for(int c = c1; c <= c2; ++c) {
      ret = ret * 10 + board[r][c] - '0';
    }
    return ret;
  };

  int ret = 0;
  for(int r = 0; r < board.size(); ++r) {
    int number_start = -1;
    for(int c = 0; c < board[0].size(); ++c) {
      if (board[r][c] >= '0' && board[r][c] <= '9') {
        if (number_start == -1) {
          number_start = c;
        }
      } else {
        if (number_start != -1) {
          int numb = get_number(r, number_start, c-1);
          for(int cc = number_start; cc < c; ++cc) {
            parts[r][cc] = numb;
          }
        }
        number_start = -1;
      }
    }
    if (number_start != -1) {
      int numb = get_number(r, number_start,  board[0].size()-1);
      for(int cc = number_start; cc <  board[0].size(); ++cc) {
        parts[r][cc] = numb;
      }
    }
  }

  for(int r = 0; r < board.size(); ++r) {
    for(int c = 0; c < board[0].size(); ++c) {
      //cout << parts[r][c] << " ";
      if (board[r][c] == '*') {
        vector<int> numbs;
        if (r > 0) {
          if (c > 0 && parts[r-1][c-1] != 0)
            numbs.push_back(parts[r-1][c-1]);
          if (parts[r-1][c] != 0 && (c == 0 || parts[r-1][c-1] == 0))
            numbs.push_back(parts[r-1][c]);
          if (c + 1 < board[0].size() && parts[r-1][c+1] != 0 && parts[r-1][c] == 0)
            numbs.push_back(parts[r-1][c+1]);
        }
        if (c > 0 && parts[r][c-1] != 0)
          numbs.push_back(parts[r][c-1]);
        if (c + 1 < board[0].size() && parts[r][c+1] != 0)
          numbs.push_back(parts[r][c+1]);
        if (r + 1 < board.size()) {
          if (c > 0 && parts[r+1][c-1] != 0)
            numbs.push_back(parts[r+1][c-1]);
          if (parts[r+1][c] != 0 && (c == 0 || parts[r+1][c-1] == 0))
            numbs.push_back(parts[r+1][c]);
          if (c + 1 < board[0].size() && parts[r+1][c+1] != 0 && parts[r+1][c] == 0)
            numbs.push_back(parts[r+1][c+1]);
        }

        assert(numbs.size() <= 2);
        if (numbs.size() == 2) {
          ret += numbs[0] * numbs[1];
        }
      }
    }
    //cout << endl;
  }

  cout << ret << endl;

  return 0;
}

