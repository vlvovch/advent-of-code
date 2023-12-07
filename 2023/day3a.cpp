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

  auto check_number = [&](int r, int c1, int c2) {
    for(int c = max(c1-1,0); c <= min(c2 + 1, (int)(board[0].size()-1)); ++c) {
      if (r > 0 && board[r - 1][c] != '.')
        return true;
      if (r + 1 < board.size() && board[r+1][c] != '.')
        return true;
    }
    if (c1 > 0 && board[r][c1-1] != '.')
      return true;
    if (c2+1 < board[0].size() && board[r][c2+1] != '.')
      return true;
    return false;
  };

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
          if (check_number(r,number_start, c-1))
            ret += get_number(r, number_start, c-1);
        }
        number_start = -1;
      }
    }
    if (number_start != -1) {
      if (check_number(r,number_start, board[0].size()-1))
        ret += get_number(r, number_start, board[0].size()-1);
    }
  }

  cout << ret << endl;

  return 0;
}

