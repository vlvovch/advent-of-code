#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif


#define _CRT_SECURE_NO_WARNINGS
#define LOCAL

using namespace std;

 map<int,pair<int,int>> dirs = {
    {0, {0, 1}},  // East
    {1, {1, 0}},  // South
    {2, {0, -1}}, // West
    {3, {-1, 0}}  // North
  };



vector<string> grid;

bool valid_coords(int r, int c) {
  return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size();
}

struct State {
  int r, c;
  int dir;
  int dir_left;
};

auto comp = [](const State& c1, const State& c2){
  if (c1.r != c2.r) return c1.r < c2.r;
  if (c1.c != c2.c) return c1.c < c2.c;
  if (c1.dir != c2.dir) return c1.dir < c2.dir;
  return c1.dir_left < c2.dir_left;
};

vector<State> all_states;

const int INT_INF = 1000000000;

int main(int argc, char* argv[])
{
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  {
    string s;
    while(cin >> s) {
      grid.push_back(s);
    }
  }
  
  // Fill all the states
  {
    all_states.push_back({0, 0, 0, 3});
    for(int r = 0; r < grid.size(); r++) {
      for(int c = 0; c < grid[0].size(); c++) {
        for(int dir = 0; dir < 4; dir++) {
          for(int dir_left = 0; dir_left < 3; dir_left++) {
            all_states.push_back({r, c, dir, dir_left});
          }
        }
      }
    }
  }

  // Fill the edges
  vector<pair<State,State>> edges;
  for(auto state : all_states) {
    // Try to continue straight
    if (state.dir_left > 0) {
      State nstate = state;
      nstate.r += dirs[state.dir].first;
      nstate.c += dirs[state.dir].second;
      nstate.dir_left--;
      if (valid_coords(nstate.r,nstate.c)) {
        edges.push_back({state, nstate});
      }
    }

    // Try to turn left
    {
      State nstate = state;
      nstate.dir = (nstate.dir + 4 - 1) % 4;
      nstate.r += dirs[nstate.dir].first;
      nstate.c += dirs[nstate.dir].second;
      nstate.dir_left = 2;
      if (valid_coords(nstate.r,nstate.c)) {
        edges.push_back({state, nstate});
      }
    }

    // Try to turn right
    {
      State nstate = state;
      nstate.dir = (nstate.dir + 1) % 4;
      nstate.r += dirs[nstate.dir].first;
      nstate.c += dirs[nstate.dir].second;
      nstate.dir_left = 2;
      if (valid_coords(nstate.r,nstate.c)) {
        edges.push_back({state, nstate});
      }
    }
  }

  cout <<  all_states.size() - 1 << " " << edges.size() << endl;

  // Bellman-Ford algorithm to find shortest path
  map<State,int,decltype(comp)> dist;
  for(auto state : all_states) {
    dist[state] = INT_INF;
  }
  dist[{0, 0, 0, 3}] = 0;
  for(int i = 0; i < all_states.size() - 1; i++) {
    int relaxed = 0;
    for(auto edge : edges) {
      State u = edge.first;
      State v = edge.second;
      int w = (int)(grid[v.r][v.c] - '0');
      if (dist[u] != INT_INF && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        relaxed++;
      }
    }
    cout << i << " " << relaxed << endl;
    if (relaxed == 0) break;
  }

  State tmp = {(int)grid.size() - 1, (int)grid[0].size() - 1, 0, 2};
  int ret = dist[tmp];
  cout << ret << endl;
  for(int dir = 0; dir < 4; dir++) {
    for(int dir_left = 0; dir_left < 3; dir_left++) {
      tmp = {(int)grid.size() - 1, (int)grid[0].size() - 1, dir, dir_left};
      ret = min(ret, dist[tmp]);
    }
  }

  // Output
  cout << ret << endl;

  return 0;
}

