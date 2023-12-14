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

  auto tilt = [&](vector<string>& grid, int dir) {
    map<int,pair<int,int>> dirs = {
      {0, {-1, 0}}, // north
      {1, {0, -1}},  // west
      {2, {1,0}},   // south
      {3, {0,1}}    // east
    };


    int dr = dirs[dir].first;
    int dc = dirs[dir].second;

    for(int tr = 0; tr < input.size(); ++tr) {
      for(int tc = 0; tc < input[tr].size(); ++tc) {
        int r = tr;
        if (dir == 2)
          r = input.size() - 1 - tr;
        int c = tc;
        if (dir == 3)
          c = input[r].size() - 1 - tc;

        if (input[r][c] == 'O') {
          int rr = r + dr;
          int cc = c + dc;
          while (rr >= 0 && rr < input.size() && cc >= 0 && cc < input[0].size() && input[rr][cc] == '.') {
            input[rr][cc] = 'O';
            input[rr-dr][cc-dc] = '.';
            rr += dr;
            cc += dc;
          }
        }
      }
    }
  };

  auto do_cycle = [&](vector<string>& grid) {
    for(int i = 0; i < 4; ++i) {
      tilt(grid, i);
    }
  };

  auto compute_load = [&](vector<string>& grid) {
    int ret = 0;
    for(int r = 0; r < grid.size(); ++r) {
      for(int c = 0; c < grid[r].size(); ++c) {
        if (grid[r][c] == 'O') {
          ret += grid.size() - r;
        }
      }
    }
    return ret;
  };

  map<vector<string>,int> inds;
  vector<int> loads;
  inds[input] = 0;
  loads.push_back(compute_load(input));
  int cycle_start = 0;
  int cycle_length = 0;

  int ind = 0;
  while (true) {
    do_cycle(input);
    ind++;
    int load = compute_load(input);
    if (inds.find(input) != inds.end()) {
      cycle_start = inds[input];
      cycle_length = ind - inds[input];
      cout << "Cycle found " << endl;
      cout << "Cycle start " << cycle_start << endl;
      cout << "Cycle length " << cycle_length << endl;
      break;
    }
    inds[input] = ind;
    loads.push_back(load);
  }


  int target_cycle = 1000000000;

  cout << loads[(target_cycle - cycle_start) % cycle_length + cycle_start] << endl;

  return 0;
}

