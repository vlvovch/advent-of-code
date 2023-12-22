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
  
  assert(grid.size() == grid[0].size());
  int N = grid.size();

  map<int,pair<int,int>> dirs = {
    {0, {0, 1}},  // East
    {1, {1, 0}},  // South
    {2, {0, -1}}, // West
    {3, {-1, 0}}  // North
  };

  int st_r, st_c;
  set<pair<int,int>> occ;
  for(int r = 0; r < N; ++r) {
    for(int c = 0; c < N; ++c) {
      if(grid[r][c] == 'S') {
        occ.insert({r, c});
        st_r = r;
        st_c = c;
        cout << "Start at " << st_r << " " << st_c << endl;
      }
    }
  }

  auto check_local_coord = [&](int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N;
  };

  map<pair<pair<int,int>,pair<int,int>>,long long> dists;
  const long long LL_INF = 1e18;
  auto compute_local_distances = [&](int from_r, int from_c) {
    set<pair<int,int>> visi;
    queue<vector<int>> q;
    q.push({from_r, from_c, 0});
    visi.insert({from_r, from_c});
    while (!q.empty()) {
      auto v = q.front();
      q.pop();
      dists[{{from_r, from_c}, {v[0], v[1]}}] = v[2];
      for(int dir = 0; dir < 4; ++dir) {
        int nr = v[0] + dirs[dir].first;
        int nc = v[1] + dirs[dir].second;
        if(check_local_coord(nr,nc) && grid[nr][nc] != '#' && visi.count({nr, nc}) == 0) {
          q.push({nr, nc, v[2]+1});
          visi.insert({nr, nc});
        }
      }
    }
    for(int r = 0; r < N; ++r) {
      for(int c = 0; c < N; ++c) {
        if(grid[r][c] != '#') {
          if (dists.count({{from_r, from_c}, {r, c}}) == 0)
            dists[{{from_r, from_c}, {r, c}}] = LL_INF;
        }
      }
    }
    return 0;
  };

  cout << "Grid size: " << N << " " << N << endl;
  compute_local_distances(st_r, st_c);

  // Which boundaries to process
  vector<vector<int>> all_steps;
  for(int dir = 0; dir < 4; ++dir) {
    vector<pair<int,int>> goals_rc = {
      {0,grid[0].size() - 1}, // Right
      {grid.size()-1,grid[0].size() - 1},   // Lower
      {grid.size()-1,0},   // Left
      {0,0}    // Upper
    };
    map<int,pair<int,int>> ndirs = {
      {0, {0, 1}},  // Right
      {1, {1, 0}},  // Down
      {2, {0, -1}}, // Left
      {3, {-1, 0}}  // Up
    };
    vector<pair<int,int>> scan_dirs = {
        {1,0},
        {0,-1},
        {-1,0},
        {0,1}
        };
    int goal_r1 = goals_rc[dir].first, goal_c1 = goals_rc[dir].second;
    vector<int> tsteps = {0, N - 1};
    for(int steps = 1; steps < N - 1; ++steps) {
      int gr = goal_r1 + scan_dirs[dir].first * steps;
      int gc = goal_c1 + scan_dirs[dir].second * steps;
      long long dist0 = dists[{{st_r,st_c},{gr,gc}}];
      int grp = goal_r1 + scan_dirs[dir].first * (steps - 1);
      int gcp = goal_c1 + scan_dirs[dir].second * (steps - 1);
      long long distp = dists[{{st_r,st_c},{grp,gcp}}];
      int grm = goal_r1 + scan_dirs[dir].first * (steps + 1);
      int gcm = goal_c1 + scan_dirs[dir].second * (steps + 1);
      long long distm = dists[{{st_r,st_c},{grm,gcm}}];
      if (dist0 < distp + 1 && dist0 < distm + 1)
        tsteps.push_back(steps);
    }
    sort(tsteps.begin(), tsteps.end());
    for(int steps : tsteps) {
      int gr = goal_r1 + scan_dirs[dir].first * steps;
      int gc = goal_c1 + scan_dirs[dir].second * steps;                    
      int nr = (gr + ndirs[dir].first + N)%N;
      int nc = (gc + ndirs[dir].second + N)%N;
      compute_local_distances(nr, nc);
    }
    all_steps.push_back(tsteps);
  }

  // Comment out unreachable plots
  for(int r = 0; r < N; ++r) {
    for(int c = 0; c < N; ++c) {
      if(grid[r][c] != '#') {
        if (dists[{{st_r, st_c}, {r, c}}] == LL_INF)
          grid[r][c] = '#';
      }
    }
  }

  // Compute number of even and odd plots within single farm
  long long cntodd = 0, cnteven = 0;
  for(int r = 0; r < N; ++r) {
    for(int c = 0; c < N; ++c) {
      if(grid[r][c] != '#') {
        long long dist = r + c;
        if (dist % 2 == 0)
          cnteven++;
        else
          cntodd++;
      }
    }
  }

  cout << "Even plots: " << cnteven << endl;
  cout << "Odd plots: " << cntodd << endl;

  // Compute after different amount of steps
  vector<long long> all_step_goals = {6, 10, 50, 100, 200, 500, 1000, 5000, 26501365};
  //all_step_goals = {400, 500, 26501365};
  for(auto steps_goal : all_step_goals)
  {
    long long ret = 0;

    // Explore the four diagonal quadrants
    vector<int> goals_r = {
      0, // Upper right
      N - 1, // Lower right
      N - 1, // Lower left
      0 // Upper left
    };
    vector<int> goals_c = {
      N - 1, // Upper right
      N - 1, // Lower right
      0, // Lower left
      0 // Upper left
    };
    for(int quad_dir = 0; quad_dir < 4; ++quad_dir)
    {
      int goal_r = goals_r[quad_dir], goal_c = goals_c[quad_dir];
      int nst_r = (goal_r == 0 ? N - 1 : 0);
      int nst_c = (goal_c == 0 ? N - 1 : 0);

      long long offset = dists[{{st_r,st_c},{goal_r,goal_c}}] + 2;

      if (steps_goal < offset)
        continue;

      bool odd_flip = steps_goal & 1;
      if (offset & 1)
        odd_flip = !odd_flip;
      if ((nst_r + nst_c) & 1)
        odd_flip = !odd_flip;
      
      // Sum inner quadrants (all odd or all even)
      long long square_cnt = (steps_goal - offset) / N;
      if (square_cnt > 1) {
        long long n1 = ((square_cnt-1) / 2) + ((square_cnt-1) % 2);
        long long cnt1 = n1 * n1;
        if (odd_flip)
          ret += cnt1 * cntodd;
        else
          ret += cnt1 * cnteven;

        long long n2 = (square_cnt-1) / 2;
        long long cnt2 = n2 * n2 + n2;
        if (N & 1)
          odd_flip = !odd_flip;
        if (odd_flip)
          ret += cnt2 * cntodd;
        else
          ret += cnt2 * cnteven;
      }

      // Sum outer quadrants
      int ilim = 1;
      if (square_cnt > 0) {
        offset += (square_cnt-1) * N;
        ilim = 0;
      }
      for(int i = ilim; i < 2; ++i) {
        for(int r = 0; r < N; ++r) {
          for(int c = 0; c < N; ++c) {
            if(grid[r][c] != '#') {
              long long dist = offset + dists[{ {nst_r,nst_c}, {r,c} }];
              if (dist <= steps_goal && (steps_goal - dist)%2 == 0)
                ret += (square_cnt + i);
            }
          }
        }
        offset += N;
      }
    }
    cout << "After quadrants: " << steps_goal << " " << ret << endl;

    // Explore the four directions
    vector<pair<int,int>> goals_rc1 = {
      {0,N - 1}, // Right
      {N-1,N - 1},   // Lower
      {N-1,0},   // Left
      {0,0}    // Upper
    };
    vector<pair<int,int>> goals_rc2 = {
      {N-1,N - 1}, // Right
      {N-1,0},   // Lower
      {0,0},   // Left
      {0,N - 1}    // Upper
    };
    map<int,pair<int,int>> ndirs = {
      {0, {0, 1}},  // Right
      {1, {1, 0}},  // Down
      {2, {0, -1}}, // Left
      {3, {-1, 0}}  // Up
    };
    
    for(int dir = 0; dir < 4; ++dir) {
      vector<long long> offsets(all_steps[dir].size(), 0);
      vector<pair<int,int>> scan_dirs = {
        {1,0},
        {0,-1},
        {-1,0},
        {0,1}
        };
      for(int isteps = 0; isteps < all_steps[dir].size(); ++isteps) {
        int steps = all_steps[dir][isteps];
        offsets[isteps] = dists[{{st_r,st_c},{goals_rc1[dir].first + scan_dirs[dir].first * steps,goals_rc1[dir].second + scan_dirs[dir].second * steps}}] + 1;
      }
      bool update_offsets = true;
      for(int cnt = 1; ; cnt++) {
        int goal_r1 = goals_rc1[dir].first, goal_c1 = goals_rc1[dir].second;
        long long offset1 = dists[{{st_r,st_c},{goal_r1,goal_c1}}] + 1
          + (cnt-1) * grid.size();
        
        int nst_r1 = (goal_r1 + ndirs[dir].first + N) % N;
        int nst_c1 = (goal_c1 + ndirs[dir].second + N) % N;
        
        if (steps_goal - offset1 >= 2 * (long long)grid.size()) {
          
          bool odd_flip = steps_goal & 1;
          if ((abs(goal_r1-st_r) + abs(goal_c1-st_c)) % 2 == 0)
            odd_flip = !odd_flip;
          if (((cnt-1) & 1) && (grid.size() & 1))
            odd_flip = !odd_flip;
          if ((nst_r1 + nst_c1) & 1)
            odd_flip = !odd_flip;
          if (odd_flip)
            ret += cntodd;
          else
            ret += cnteven;
          
          if (update_offsets) {
            auto new_offsets = offsets;
            for(int isteps = 0; isteps < all_steps[dir].size(); ++isteps) {
              int steps = all_steps[dir][isteps];
              for(int isteps_prev = 0; isteps_prev < all_steps[dir].size(); ++isteps_prev) {
                int steps_prev = all_steps[dir][isteps_prev];
                long long cand = offsets[isteps_prev] + 
                dists[{{nst_r1 + scan_dirs[dir].first * steps_prev,
                  nst_c1 + scan_dirs[dir].second * steps_prev},
                  {goals_rc1[dir].first + scan_dirs[dir].first * steps,
                  goals_rc1[dir].second + scan_dirs[dir].second * steps}}] + 1;
                if (new_offsets[isteps] == offsets[isteps] || cand < new_offsets[isteps])
                  new_offsets[isteps] = cand;
              }
            }
            auto cand_offsets = offsets;
            for(int isteps = 0; isteps < all_steps[dir].size(); ++isteps) 
              cand_offsets[isteps] += N;
            
            if (cand_offsets == new_offsets)
              update_offsets = false;
            offsets = new_offsets;
          } else {
            for(int isteps = 0; isteps < all_steps[dir].size(); ++isteps) 
              offsets[isteps] += N;
          }
        } else {
          int goal_r1 = goals_rc1[dir].first, goal_c1 = goals_rc1[dir].second;
          int nst_r1 = (goal_r1 + ndirs[dir].first + N) % N;
          int nst_c1 = (goal_c1 + ndirs[dir].second + N) % N;
          // Consider up to three extra cubes
          for(int i = 0; i < 3; ++i) {
            for(int r = 0; r < N; ++r) {
              for(int c = 0; c < N; ++c) {
                if(grid[r][c] != '#') {
                  for(int isteps = 0; isteps < offsets.size(); ++isteps) {
                    int steps = all_steps[dir][isteps];
                    int gr = goal_r1 + scan_dirs[dir].first * steps;
                    int gc = goal_c1 + scan_dirs[dir].second * steps;
                    int nr = nst_r1 + scan_dirs[dir].first * steps;
                    int nc = nst_c1 + scan_dirs[dir].second * steps;
                    long long tdist = offsets[isteps] + dists[{{nr,nc},{r,c}}];
                    if (tdist <= steps_goal && (steps_goal - tdist)%2 == 0) {
                      ret++;
                      break;
                    }
                  }
                }
              }
            }

            {
              auto new_offsets = offsets;
              for(int isteps = 0; isteps < all_steps[dir].size(); ++isteps) {
                int steps = all_steps[dir][isteps];
                for(int isteps_prev = 0; isteps_prev < all_steps[dir].size(); ++isteps_prev) {
                  int steps_prev = all_steps[dir][isteps_prev];
                  long long cand = offsets[isteps_prev] + 
                  dists[{{nst_r1 + scan_dirs[dir].first * steps_prev,
                    nst_c1 + scan_dirs[dir].second * steps_prev},
                    {goals_rc1[dir].first + scan_dirs[dir].first * steps,
                    goals_rc1[dir].second + scan_dirs[dir].second * steps}}] + 1;
                  if (new_offsets[isteps] == offsets[isteps] || cand < new_offsets[isteps])
                    new_offsets[isteps] = cand;
                }
              }
              offsets = new_offsets;
            }
          }
          break;
        }
      }
    }
    cout << "After the four beams: " << steps_goal << " " << ret << endl;

    // Compute the inner grid
    for(int r = 0; r < N; ++r) {
      for(int c = 0; c < N; ++c) {
        if(grid[r][c] != '#') {
          long long dist = dists[{{st_r,st_c},{r,c}}];
          if (dist <= steps_goal && (steps_goal - dist)%2 == 0) {
            ret++;
          }
        }
      }
    }

    cout << "After the initial grid: " << steps_goal << " " << ret << endl;

    if (steps_goal == 26501365) {
      cout << "Part 2 answer: " << ret << endl;
    }
  }

  return 0;
}

