#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif


#define _CRT_SECURE_NO_WARNINGS
#define LOCAL

using namespace std;

// Use Dijkstra's algorithm instead of Bellman-Ford
// This is much faster

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
  int dir_taken;
};

auto comp = [](const State& c1, const State& c2){
  if (c1.r != c2.r) return c1.r < c2.r;
  if (c1.c != c2.c) return c1.c < c2.c;
  if (c1.dir != c2.dir) return c1.dir < c2.dir;
  return c1.dir_taken < c2.dir_taken;
};

auto comp2 = [](const pair<int,State>& a, const pair<int,State>& b) {
  return a.first > b.first;
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
    all_states.push_back({0, 0, 0, 0});
    for(int r = 0; r < grid.size(); r++) {
      for(int c = 0; c < grid[0].size(); c++) {
        for(int dir = 0; dir < 4; dir++) {
          for(int dir_taken = 1; dir_taken < 11; dir_taken++) {
            all_states.push_back({r, c, dir, dir_taken});
          }
        }
      }
    }
  }

  // Fill the edges
  map<State,vector<State>,decltype(comp)> graph;
  for(auto state : all_states) {
    graph[state] = {};
    // Try to continue straight
    if (state.dir_taken < 10) {
      State nstate = state;
      nstate.r += dirs[state.dir].first;
      nstate.c += dirs[state.dir].second;
      nstate.dir_taken++;
      if (valid_coords(nstate.r,nstate.c)) {
        graph[state].push_back(nstate);
      }
    }

    // Try to turn left
    if (state.dir_taken >= 4)
    {
      State nstate = state;
      nstate.dir = (nstate.dir + 4 - 1) % 4;
      nstate.r += dirs[nstate.dir].first;
      nstate.c += dirs[nstate.dir].second;
      nstate.dir_taken = 1;
      if (valid_coords(nstate.r,nstate.c)) {
        graph[state].push_back(nstate);
      }
    }

    // Try to turn right
    if (state.dir_taken >= 4)
    {
      State nstate = state;
      nstate.dir = (nstate.dir + 1) % 4;
      nstate.r += dirs[nstate.dir].first;
      nstate.c += dirs[nstate.dir].second;
      nstate.dir_taken = 1;
      if (valid_coords(nstate.r,nstate.c)) {
        graph[state].push_back(nstate);
      }
    }
  }

  cout << "Graph size: " << all_states.size() - 1 << endl;

  // Dijkstra algorithm to find shortest path
  set<State,decltype(comp)> visited;
  map<State,int,decltype(comp)> dist;
  priority_queue<pair<int,State>,vector<pair<int,State>>,decltype(comp2)> pq;
  for(auto state : all_states) {
    dist[state] = INT_INF;
    //pq.push({INT_INF, state});
  }
  dist[{0, 0, 0, 0}] = 0;
  pq.push({0, {0, 0, 0, 0}});

  while(!pq.empty()) {
    auto top = pq.top();
    pq.pop();
    State u = top.second;
    if (visited.count(u) > 0) 
      continue;
    visited.insert(u);
    for(auto v : graph[u]) {
      int w = (int)(grid[v.r][v.c] - '0');
      if (dist[u] != INT_INF && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
    }
  }

  State tmp = {(int)grid.size() - 1, (int)grid[0].size() - 5, 0, 1};
  int tsum = 0;
  for(int i = 0; i < 4; i++) {
    tsum += (int)(grid[(int)grid.size() - 1][(int)grid[0].size() - 4 + i] - '0');
  }
  int ret = dist[tmp] + tsum;
  for(int dir_taken = 1; dir_taken < 11; dir_taken++) {
    for(int dir = 0; dir < 4; ++dir) {
      tmp = {(int)grid.size() - 1, (int)grid[0].size() - 5, dir, dir_taken};
      ret = min(ret, dist[tmp] + tsum);
    }
  }
  tsum = 0;
  for(int i = 0; i < 4; i++) {
    tsum += (int)(grid[(int)grid.size() - 4 + i][(int)grid[0].size() - 1] - '0');
  }
  for(int dir_taken = 1; dir_taken < 11; dir_taken++) {
    for(int dir = 0; dir < 4; ++dir) {
      tmp = {(int)grid.size() - 5, (int)grid[0].size() - 1, dir, dir_taken};
      ret = min(ret, dist[tmp] + tsum);
    }
  }

  // Output
  cout << ret << endl;

  return 0;
}

