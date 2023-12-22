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

  set<pair<int,int>> occ;
  for(int r = 0; r < grid.size(); ++r) {
    for(int c = 0; c < grid[0].size(); ++c) {
      if(grid[r][c] == 'S') {
        occ.insert({r, c});
      }
    }
  }

  auto check_valid_coord = [&](int r, int c) {
    return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
  };

  auto make_step = [&]() {
    set<pair<int,int>> new_occ;
    for(auto el : occ) {
      for(int dir = 0; dir < 4; ++dir) {
        int nr = el.first + dirs[dir].first;
        int nc = el.second + dirs[dir].second;
        if(check_valid_coord(nr,nc) && grid[nr][nc] != '#') {
          new_occ.insert({nr, nc});
        }
      }
    }
    occ = new_occ;
  };

  int steps = 0;
  for(;steps < 6; steps++) {
    make_step();
  }
  cout << "After " << steps << " steps occupied " << occ.size() << endl;

  for(;steps < 64; steps++) {
    make_step();
  }
  cout << "After " << steps << " steps occupied " << occ.size() << endl;

  return 0;
}

