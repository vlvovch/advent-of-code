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

  map<char, pair<int,int>> dirs = {
    {'R', {0, 1}},  // East
    {'D', {1, 0}},  // South
    {'L', {0, -1}}, // West
    {'U', {-1, 0}}  // North
  };

  struct Command {
    char dir;
    int steps;
    string color;
  };

  vector<Command> commands;

  int maxr = 0, maxc = 0;
  int minr = 0, minc = 0;
  {
    int cr = 0, cc = 0;
    
    Command cmd;
    while (cin >> cmd.dir >> cmd.steps >> cmd.color) {
      commands.push_back(cmd);
      cr += dirs[cmd.dir].first * cmd.steps;
      cc += dirs[cmd.dir].second * cmd.steps;
      maxr = max(maxr, cr);
      maxc = max(maxc, cc);
      minr = min(minr, cr);
      minc = min(minc, cc);
    }
    cout << maxr << " " << maxc << endl;
    cout << minr << " " << minc << endl;
    cout << cr << " " << cc << endl;
  }

  map<pair<char,char>,char> turns = {
    {{'R','D'}, '7'},
    {{'R','U'}, 'J'},
    {{'D','R'}, 'L'},
    {{'D','L'}, 'J'},
    {{'L','D'}, 'F'},
    {{'L','U'}, 'L'},
    {{'U','R'}, 'F'},
    {{'U','L'}, '7'}
  };


  vector<string> grid = vector<string>(maxr-minr+1, string(maxc-minc+1, '.'));
  vector<string> grid2 = grid;
  {
    int cr = -minr, cc = -minc;
    int icom = 0;
    for(auto& command : commands) {
      //cout << command.dir << " " << command.steps << " " << command.color << endl;
      for(int i = 0; i < command.steps; ++i) {
        cr += dirs[command.dir].first;
        cc += dirs[command.dir].second;
        grid[cr][cc] = '#';
        if (command.dir == 'R' || command.dir == 'L') {
          grid2[cr][cc] = '-';
        } else {
          grid2[cr][cc] = '|';
        }
        if (i == command.steps - 1) {
          grid2[cr][cc] = turns[{commands[icom].dir, commands[(icom+1)%commands.size()].dir}];
        }
        
      }
      icom++;
    }
  }

  for(auto& row : grid2) {
    cout << row << endl;
  }

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

  vector<string> ngrid = grid;

  int ret = 0;
  for(int r = 0; r < grid.size(); ++r) {
    for(int c = 0; c < grid[r].size(); ++c) {
      if (grid[r][c] == '#') {
        ret++;
      } else {
        if (ray_trace(r, c) & 1) {
          ngrid[r][c] = '#';
          ret++;
        }
      }
    }
  }

  cout << endl;
  for(auto& row : ngrid) {
    cout << row << endl;
  }

  // Output
  cout << ret << endl;

  return 0;
}

