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

  vector<string> grid;
  {
    string s;
    while(cin >> s) {
      grid.push_back(s);
    }
  }

  map<int,pair<int,int>> dirs = {
    {0, {0, 1}},  // East
    {1, {1, 0}},  // South
    {2, {0, -1}}, // West
    {3, {-1, 0}}  // North
  };

  vector<vector<vector<int>>> lasers(grid.size(), vector<vector<int>>(grid[0].size(), vector<int>(4, 0)));

  std::function<void(int,int,int)> laser = [&](int r, int c, int dir) {
    if(r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size()) return;
    if(lasers[r][c][dir] != 0) return;
    lasers[r][c][dir] = 1;

    if(grid[r][c] == '.') {
      int nr = r + dirs[dir].first;
      int nc = c + dirs[dir].second;
      laser(nr, nc, dir);
    }

    if(grid[r][c] == '/') {
      map<int,int> tdirs = {
        {0, 3},
        {1, 2},
        {2, 1},
        {3, 0}
      };
      int ndir = tdirs[dir];
      int nr = r + dirs[ndir].first;
      int nc = c + dirs[ndir].second;
      laser(nr, nc, ndir);
    }

    if(grid[r][c] == '\\') {
      map<int,int> tdirs = {
        {0, 1},
        {1, 0},
        {2, 3},
        {3, 2}
      };
      int ndir = tdirs[dir];
      int nr = r + dirs[ndir].first;
      int nc = c + dirs[ndir].second;
      laser(nr, nc, ndir);
    }

    if(grid[r][c] == '|') {
      if (dir == 1 || dir == 3) {
        int nr = r + dirs[dir].first;
        int nc = c + dirs[dir].second;
        laser(nr, nc, dir);
      } else {
        laser(r - 1, c, 3);
        laser(r + 1, c, 1);
      }
    }

    if(grid[r][c] == '-') {
      if (dir == 0 || dir == 2) {
        int nr = r + dirs[dir].first;
        int nc = c + dirs[dir].second;
        laser(nr, nc, dir);
      } else {
        laser(r, c - 1, 2);
        laser(r, c + 1, 0);
      }
    }
  };

  auto compute_energized = [&]() {
    int ret = 0;
    for(int r = 0; r < grid.size(); ++r) {
      for(int c = 0; c < grid[0].size(); ++c) {
        int tcnt = 0;
        for(int dir = 0; dir < 4; ++dir) {
          tcnt += lasers[r][c][dir];
        }
        if (tcnt > 0)
          ret++;
      }
    }
    return ret;
  };

  int ret = 0;
  for(int c = 0; c < grid[0].size(); ++c) {
    lasers = vector<vector<vector<int>>>(grid.size(), vector<vector<int>>(grid[0].size(), vector<int>(4, 0)));
    laser(0, c, 1);
    ret = max(ret, compute_energized());
  }
  for(int c = 0; c < grid[0].size(); ++c) {
    lasers = vector<vector<vector<int>>>(grid.size(), vector<vector<int>>(grid[0].size(), vector<int>(4, 0)));
    laser(grid.size()-1, c, 3);
    ret = max(ret, compute_energized());
  }
  for(int r = 0; r < grid.size(); ++r) {
    lasers = vector<vector<vector<int>>>(grid.size(), vector<vector<int>>(grid[0].size(), vector<int>(4, 0)));
    laser(r, 0, 0);
    ret = max(ret, compute_energized());
  }
  for(int r = 0; r < grid.size(); ++r) {
    lasers = vector<vector<vector<int>>>(grid.size(), vector<vector<int>>(grid[0].size(), vector<int>(4, 0)));
    laser(r, grid[0].size()-1, 2);
    ret = max(ret, compute_energized());
  }
  
  // Output
  cout << ret << endl;

  return 0;
}

