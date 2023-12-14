#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif


#define _CRT_SECURE_NO_WARNINGS
#define LOCAL

using namespace std;

// How many characters are different between two strings
int string_difference(const string& s1, const string& s2) {
  int ret = 0;
  for(int i = 0; i < s1.size(); ++i) {
    ret += (s1[i] != s2[i]);
  }
  return ret;
}

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
      int diffcnt = 0;
      bool fl = true;
      for(int cc = 0; cc < c && fl && (cc+c) < gridcol.size(); ++cc) {
        // Number of different characters
        int tdif = string_difference(gridcol[c-cc-1], gridcol[c+cc]);

        // Can be at most 1 different character
        fl &= (tdif <= 1);

        // Add to total number of smudges needed
        diffcnt += tdif;
      }

      // Can have only one smudge
      if (fl && diffcnt == 1) {
        cout << "c " << ind << " " << c << endl;
        ret += c;
      }
    }

    // Same check for horizontal reflections
    for(int r = 1; r < grid.size(); ++r) {
      int diffcnt = 0;
      bool fl = true;
      for(int rr = 0; rr < r && fl && (rr + r) < grid.size(); ++rr) {
        int tdif = string_difference(grid[r-rr-1], grid[r+rr]);
        fl &= (tdif <= 1);
        diffcnt += tdif;
      }
      if (fl && diffcnt == 1) {
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

