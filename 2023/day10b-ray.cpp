#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif


#define _CRT_SECURE_NO_WARNINGS
#define LOCAL

using namespace std;

// More efficient implementation of part B using ray intersection

int main(int argc, char* argv[])
{
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  vector<string> grid;
  string s;
  while(cin >> s) {
    grid.push_back(s);
  }

  map<char,pair<pair<int,int>,pair<int,int>>> dir = {
    {'|', {{1, 0}, {-1,0}}},
    {'-', {{0,1}, {0,-1}}},
    {'L', {{-1,0}, {0,1}}},
    {'J', {{-1,0},{0,-1}}},
    {'7', {{1,0}, {0,-1}}},
    {'F', {{0,1}, {1,0}}},
    {'.', {{0, 0}, {0,0}}},
    {'S', {{0, 0}, {0,0}}},
    {'O', {{0, 0}, {0,0}}}
    };
  
  int st_r = 0, st_c = 0;
  for(int r = 0; r < grid.size(); ++r) {
    for(int c = 0; c < grid[r].size(); ++c) {
      if (grid[r][c] == 'S') {
        st_r = r;
        st_c = c;
        break;
      }
    }
  }

  cout << st_r << " " << st_c << endl;

  for(auto el : dir) {
    if (el.first != '.') {
      char symb = el.first;
      pair<pair<int,int>,pair<int,int>> d = el.second;
      int nr1 = st_r + d.first.first;
      int nc1 = st_c + d.first.second;
      int nr2 = st_r + d.second.first; 
      int nc2 = st_c + d.second.second;
      if (nr1 < 0 || nr1 >= grid.size() || nc1 < 0 || nc1 >= grid[0].size())
        continue;
      char symb1 = grid[nr1][nc1];
      char symb2 = grid[nr2][nc2];
      bool fl = true;
      fl &= (nr1 + dir[symb1].second.first == st_r 
        && nc1 + dir[symb1].second.second == st_c)
        || (nr1 + dir[symb1].first.first == st_r
        && nc1 + dir[symb1].first.second == st_c);
      fl &= (nr2 + dir[symb2].second.first == st_r 
        && nc2 + dir[symb2].second.second == st_c)
        || (nr2 + dir[symb2].first.first == st_r
        && nc2 + dir[symb2].first.second == st_c);
      if (fl) {
        cout << "S = " << symb << endl;
        grid[st_r][st_c] = symb;
        break;
      }
    }
  }

  vector<string> grid2(grid.size(), string(grid[0].size(), '.'));

  int loop_size = 1;
  int pr = st_r, pc = st_c;
  int nr = st_r + dir[grid[st_r][st_c]].first.first;
  int nc = st_c + dir[grid[st_r][st_c]].first.second;
  grid2[pr][pc] = grid[pr][pc];
  while (!(nr == st_r && nc == st_c)) {
    cout.flush();
    char symb = grid[nr][nc];
    if (nr + dir[symb].second.first == pr
        && nc + dir[symb].second.second == pc) {
          pr = nr;
          pc = nc;
          nr += dir[grid[pr][pc]].first.first;
          nc += dir[grid[pr][pc]].first.second;
        }
    else {
      pr = nr;
      pc = nc;
      nr += dir[grid[pr][pc]].second.first;
      nc += dir[grid[pr][pc]].second.second;
    }
    grid2[pr][pc] = grid[pr][pc];
    loop_size++;
  }

  cout << "Farthest point = " << loop_size/2 + (loop_size%2) << endl;

  // Compute number of intersections with the loop of a ray to the east
  auto ray_trace = [&](int r, int c) {
    int ret = 0;
    // Move east
    int nc = c + 1;
    char prev = '.';
    while(nc < grid2[r].size()) {
      if (grid2[r][nc] == '|')
        ret++;
      if (grid2[r][nc] == 'J' && prev == 'F') {
        ret++;
        prev = '.';
      }
      if (grid2[r][nc] == '7' && prev == 'L') {
        ret++;
        prev = '.';
      }
      if (grid2[r][nc] == 'F' || grid2[r][nc] == 'L') {
        prev = grid2[r][nc];
      }
      else if (grid2[r][nc] != '-')
        prev = '.';
      nc++;
    }
    return ret;
  };

  int ret = 0;
  // Brute force each candidate
  for(int r = 0; r < grid2.size(); ++r) {
    for(int c = 0; c < grid2[r].size(); ++c) {
      if (grid2[r][c] == '.' && ray_trace(r, c)%2 != 0) {
        ret++;
      }
    }
  }

  cout << "Points inside: " << ret << endl;

  return 0;
}

