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

  int st_r = 0, st_c = 0;
  for(int c = 0; c < grid[0].size(); ++c) {
    if (grid[0][c] == '.') {
      st_r = 0;
      st_c = c;
      cout << "Start at " << st_r << " " << st_c << endl;
      break;
    }
  }
  
  map<char,int> slopes_dir = {
    {'>', 0},
    {'v', 1},
    {'<', 2},
    {'^', 3}
    };

  map<int,pair<int,int>> dirs = {
    {0, {0, 1}},  // East
    {1, {1, 0}},  // South
    {2, {0, -1}}, // West
    {3, {-1, 0}}  // North
  };

  int N = grid.size(), M = grid[0].size();
  vector<vector<int>> visited(N, vector<int>(M, 0));
  int ret = 0;
  int tret = 0;
  
  function<void(int r, int c)> go = [&](int r, int c) {
    visited[r][c] = 1;
    tret++;

    if (r == N - 1) {
      ret = max(ret, tret);
      visited[r][c] = 0;
      tret--;
      return;
    }

    for(int dir = 0; dir < 4; ++dir) {
      int nr = r + dirs[dir].first;
      int nc = c + dirs[dir].second;
      if (nr >= 0 && nr < N && nc >= 0 && nc < M && !visited[nr][nc] && grid[nr][nc] != '#') {
        if (grid[nr][nc] == '.' || slopes_dir[grid[nr][nc]] == dir) {
          go(nr, nc);
        }
      }
    }

    visited[r][c] = 0;
    tret--;
  };

  go(st_r, st_c);

  cout << "Part 1 answer: " << ret - 1 << endl;

  // Part 2

  // Find the nodes
  vector<pair<int,int>> nodes;
  map<pair<int,int>,int> nodes_map;
  for(int r = 0; r < N; ++r) {
    for(int c = 0; c < M; ++c) {
      if ((r == 0 || r == N - 1) && grid[r][c] == '.') {
        nodes.push_back({r,c});
        nodes_map[{r,c}] = nodes.size() - 1;
      }
      else if (grid[r][c] != '#') {
        int neighbors = 0;
        for(int dir = 0; dir < 4; ++dir) {
          int nr = r + dirs[dir].first;
          int nc = c + dirs[dir].second;
          if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != '#') {
            neighbors++;
          }
        }
        if (neighbors > 2) {
          nodes.push_back({r,c});
          nodes_map[{r,c}] = nodes.size() - 1;
        }
      }
    }
  }

  cout << "Nodes: " << nodes.size() << endl;

  // Find the edges
  vector<vector<pair<int,int>>> graph(nodes.size(), vector<pair<int,int>>());
  vector<vector<int>> edges;
  // Compute all edges from given nodes
  {
    int tlen = 0, from_r = st_r, from_c = st_c;
    function<void(int,int,int,int)> go_graph_edges = [&](int r, int c, int prev_r, int prev_c) {
      //tlen++;
      if (nodes_map.count({r,c}) > 0 && (r != from_r || c != from_c)) {
        int u = nodes_map[{from_r, from_c}];
        int v = nodes_map[{r, c}];
        graph[u].push_back({v, tlen});
        edges.push_back({u, v, tlen});
      } else {
        int cnt = 0;
        for(int dir = 0; dir < 4; ++dir) {
          int nr = r + dirs[dir].first;
          int nc = c + dirs[dir].second;
          if (nr >= 0 && nr < N && nc >= 0 && nc < M && grid[nr][nc] != '#') {
            if (nr != prev_r || nc != prev_c) {
              cnt++;
              tlen++;
              go_graph_edges(nr, nc, r, c);
              tlen--;
            }
          }
        }
      }
    };
    for(auto node : nodes) {
      from_r = node.first;
      from_c = node.second;
      go_graph_edges(from_r, from_c, -1, -1);
    }
  }

  ret = 0;
  tret = 0;

  vector<int> visited_nodes(nodes.size(), 0);
  function<void(int v)> go_hard = [&](int v) {
    visited_nodes[v] = 1;

    if (v == nodes.size() - 1) {
      ret = max(ret, tret);
      visited_nodes[v] = 0;
      return;
    }

    for(auto u : graph[v]) {
      if (visited_nodes[u.first] == 0) {
        tret += u.second;
        go_hard(u.first);
        tret -= u.second;
      }
    }
    
    visited_nodes[v] = 0;
  };

  go_hard(0);

  cout << "Part 2 answer: " << ret << endl;

  return 0;
}

