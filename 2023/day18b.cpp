#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif

// Solves both Part A & B

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

  map<int,char> dirmap2 = {
    {0, 'R'},
    {1, 'D'},
    {2, 'L'},
    {3, 'U'}
  };

  struct Command {
    char dir;
    long long steps;
    string color;
  };

  vector<Command> commands_orig;
  vector<Command> commands_new;

  long long maxr = 0, maxc = 0;
  long long minr = 0, minc = 0;
  {
    long long cr = 0, cc = 0;
    
    Command cmd;
    while (cin >> cmd.dir >> cmd.steps >> cmd.color) {
      commands_orig.push_back(cmd);
      cmd.dir = dirmap2[cmd.color[cmd.color.size() - 2] - '0'];
      long long nsteps = 0;
      for(int i = 2; i < cmd.color.size() - 2; i++) {
        nsteps *= 16;
        if (cmd.color[i] <= '9')
          nsteps += cmd.color[i] - '0';
        else
          nsteps += 10 + cmd.color[i] - 'a';
      }
      cmd.steps = nsteps;

      commands_new.push_back(cmd);
      cout << cmd.dir << " " << cmd.steps << endl;

      cr += dirs[cmd.dir].first * cmd.steps;
      cc += dirs[cmd.dir].second * cmd.steps;
      maxr = max(maxr, cr);
      maxc = max(maxc, cc);
      minr = min(minr, cr);
      minc = min(minc, cc);
    }
  }

  for(int ipart = 0; ipart < 2; ++ipart) {

    cout << "Solving part " << ipart + 1 << "..." << endl;

    long long ret = 0;
    long long perimeter = 0;
    vector<Command> commands;
    if (ipart == 0) 
      commands = commands_orig;
    else
      commands = commands_new;

    vector<pair<double,double>> coords;
    {
      long long cr = 0, cc = 0;
      for(int ic = 0; ic < commands.size(); ic++) {
        coords.push_back({cr, cc});
        perimeter += commands[ic].steps;
        long long nr = cr + dirs[commands[ic].dir].first * commands[ic].steps;
        long long nc = cc + dirs[commands[ic].dir].second * commands[ic].steps;
        cr = nr;
        cc = nc;
      }
    }

    vector<vector<pair<long long,long long>>> coords_sides;
    {
      vector<pair<long long,long long>> coords_side_move = {
        {-1, -1},
        {-1, 1},
        {1, -1},
        {1, 1}
      };
      for(int isid = 0; isid < 4; ++isid) {
        vector<pair<long long,long long>> coords_side2;
        long long cr = 0, cc = 0;
        double rside = coords_side_move[isid].first;
        double cside = coords_side_move[isid].second;
        for(int ic = 0; ic < commands.size(); ic++) {
          coords_side2.push_back({2*cr + rside, 2*cc + cside});
          auto new_command = commands[(ic+1)%commands.size()];
          auto old_command = commands[(ic -1 + commands.size())%commands.size()];
          auto command = commands[ic];
          if (new_command.dir != old_command.dir) {
            if (command.dir == 'R' || command.dir == 'L') {
              cside = -cside;
            } else {
              rside = -rside;
            }
          }
          cr += dirs[command.dir].first * command.steps;
          cc += dirs[command.dir].second * command.steps;
        }
        coords_sides.push_back(coords_side2);
      }
    }
    
    vector<long long> areas;
    for(int isid = 0; isid < 4; ++isid) {
      double area = 0;
      for(int ic = 0; ic < coords_sides[isid].size(); ++ic) {
        area += coords_sides[isid][ic].first * coords_sides[isid][(ic+1)%coords.size()].second;
        area -= coords_sides[isid][ic].second * coords_sides[isid][(ic+1)%coords.size()].first;
      }
      areas.push_back(abs(area));
      //cout << "Area = " << areas.back() << endl;
    }
    // Output
    cout << "Perimeter: " << perimeter << endl;
    //cout << *min_element(areas.begin(), areas.end()) / 8 + perimeter << endl;
    //cout << *max_element(areas.begin(), areas.end()) / 8 << endl;
    cout << "Answer: " << *max_element(areas.begin(), areas.end()) / 8 << endl;
    cout << endl;
  }

  return 0;
}

