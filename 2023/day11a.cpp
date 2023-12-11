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

  vector<string> space;
  string s;
  while(cin >> s) {
    space.push_back(s);
  }

  // Expand the galaxy
  vector<int> rows, cols;
  for(int r = 0; r < space.size(); ++r) {
    bool empty = true;
    for(int c = 0; c < space[r].size(); ++c) {
      if (space[r][c] != '.') {
        empty = false;
        break;
      }
    }
    if (empty) {
      rows.push_back(r);
    }
  }
  for(int c = 0; c < space[0].size(); ++c) {
    bool empty = true;
    for(int r = 0; r < space.size(); ++r) {
      if (space[r][c] != '.') {
        empty = false;
        break;
      }
    }
    if (empty) {
      cols.push_back(c);
      //cout << c << endl;
    }
  }

  vector<string> new_space;
  for(int r = 0; r < space.size(); ++r) {
    new_space.push_back(space[r]);
    if (find(rows.begin(), rows.end(), r) != rows.end()) {
      new_space.push_back(string(space[r].size(), '.'));
    }
  }
  int colcnt = 0;
  for(int ncol : cols) {
    for(int r = 0; r < new_space.size(); ++r) {
      new_space[r].insert(new_space[r].begin() + ncol + colcnt, '.');
    }
    colcnt++;
  }

  for(auto& s : new_space) {
    cout << s << endl;
  }

  // Find the galaxies
  vector<pair<int,int>> galaxies;
  for(int r = 0; r < new_space.size(); ++r) {
    for(int c = 0; c < new_space[r].size(); ++c) {
      if (new_space[r][c] == '#') {
        galaxies.push_back({r,c});
      }
    }
  }

  int ret = 0;
  // Sum the paths
  for(int i = 0; i < galaxies.size(); ++i) {
    for(int j = i + 1; j < galaxies.size(); ++j) {
      int r1 = galaxies[i].first, c1 = galaxies[i].second;
      int r2 = galaxies[j].first, c2 = galaxies[j].second;
      int dr = abs(r2 - r1), dc = abs(c2 - c1);
      ret += dr + dc;
    }
  }

  // Output
  cout << ret << endl;

  return 0;
}

