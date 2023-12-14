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

  int ret = 0;

  char cc[1000];
  string s;
  int ind = 0;
  while(cin.getline(cc, 1000)) {
    s = string(cc);
    vector<string> grid;
    vector<string> gridcol;
    grid.clear();
    grid.push_back(s);
    while(s != "" && cin.getline(cc, 1000)) {
      s = string(cc);
      if (s != "")
        grid.push_back(s);
    }

    // Make columns
    for(int c = 0; c < grid[0].size(); ++c) {
      string col;
      for(int r = 0; r < grid.size(); ++r) {
        col.push_back(grid[r][c]);
      }
      gridcol.push_back(col);
    }

    // Check vertical reflections
    for(int c = 1; c < gridcol.size(); ++c) {
      bool fl = true;
      for(int cc = 0; cc < c && fl && (cc+c) < gridcol.size(); ++cc) {
        fl &= (gridcol[c-cc-1] == gridcol[c+cc]);
      }
      if (fl) {
        cout << "c " << ind << " " << c << endl;
        ret += c;
      }
    }

    // Check horizontal reflections
    for(int r = 1; r < grid.size(); ++r) {
      bool fl = true;
      for(int rr = 0; rr < r && fl && (rr + r) < grid.size(); ++rr) {
        fl &= (grid[r-rr-1] == grid[r+rr]);
      }
      if (fl) {
        cout << "r " << ind << " " << r << endl;
        ret += 100 * r;
      }
    }

    ind++;
  }

  // Output
  cout << ret << endl;

  return 0;
}

