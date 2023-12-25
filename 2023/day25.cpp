#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif


#define _CRT_SECURE_NO_WARNINGS
#define LOCAL

using namespace std;

// Split string using delimiter
std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string& s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

int main(int argc, char* argv[])
{
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  map<string,int> map_comps;
  vector<vector<int>> g;
  vector<pair<int,int>> edges;
  vector<string> str_comps;

  // Read the input
  {
    char cc[1000];
    while(cin.getline(cc, 1000)) {
      auto res = split(cc, ' ');
      assert(res[0].size() == 4);
      assert(res[0][3] == ':');
      string ustr = res[0].substr(0, 3);
      if (map_comps.find(ustr) == map_comps.end()) {
        map_comps[ustr] = map_comps.size();
        g.push_back(vector<int>());
        str_comps.push_back(ustr);
      }
      for(int iv = 1; iv < res.size(); ++iv) {
        string vstr = res[iv];
        if (map_comps.find(vstr) == map_comps.end()) {
          map_comps[vstr] = map_comps.size();
          g.push_back(vector<int>());
          str_comps.push_back(vstr);
        }
        int u = map_comps[ustr];
        int v = map_comps[vstr];
        g[u].push_back(v);
        g[v].push_back(u);
        edges.push_back({u, v});
      }
    }
  }

  cout << "Components: " << g.size() << endl; 
  cout << "Wires: " << edges.size() << endl;

  // BFS shortests paths from 0
  vector<int> dist(g.size(), -1);
  {
    queue<int> q;
    q.push(0);
    dist[0] = 0;
    while(!q.empty()) {
      int u = q.front();
      q.pop();
      for(auto v : g[u]) {
        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }
    }
  }

  // Longest shortest path
  int max_dist = 0;
  int max_dist_i = 0;
  {
    for(int i = 0; i < dist.size(); ++i) {
      auto el = dist[i];
      max_dist = max(max_dist, el);
      max_dist_i = i;
    }
    cout << "Max dist: " << max_dist << " between " << str_comps[0] << " and " << str_comps[max_dist_i] << endl;
  }

  // We will try to exlcluded edges from the longest shortest path
  // assuming vertices 0 and max_dist_i are from disconnected components

  set<pair<int,int>> edge_excl;

  // BFS find the shortest path to vertex vgoal
  auto find_path = [&](int vgoal) {
    int i = 0;
    vector<int> totpath = {};
    queue<vector<int>> q;
    q.push({i});
    vector<int> visited(g.size(), 0);
    visited[i] = 1;
    int comp_size = 0;
    while(!q.empty()) {
      auto cpath = q.front();
      int u = cpath.back();
      q.pop();
      comp_size++;
      for(auto v : g[u]) {
        if (visited[v] == 0 && edge_excl.count({u,v}) == 0 && edge_excl.count({v,u}) == 0) {
          visited[v] = 1;
          auto tpath = cpath;
          tpath.push_back(v);
          q.push(tpath);
          if (v == vgoal)
            totpath = tpath;
        }
      }
    }
    return make_pair(totpath, comp_size);
  };

  auto path1 = find_path(max_dist_i).first;
  for(int ie1 = 0; ie1 < path1.size() - 1; ie1++) {
    edge_excl.insert({path1[ie1], path1[ie1 + 1]});
    auto path2 = find_path(max_dist_i).first;
    assert(path2.size() > 0);
    for(int ie2 = 0; ie2 < path2.size() - 1; ie2++) {
      edge_excl.insert({path2[ie2], path2[ie2 + 1]});
      auto path3 = find_path(max_dist_i).first;
      assert(path3.size() > 0);
      for(int ie3 = 0; ie3 < path3.size(); ie3++) {
        edge_excl.insert({path3[ie3], path3[ie3 + 1]});
        auto path4 = find_path(max_dist_i);
        if (path4.first.size() == 0) {
          cout << "Answer: " << path4.second * (g.size() - path4.second) << endl;
          return 0;
        }
        edge_excl.erase({path3[ie3], path3[ie3 + 1]});
      }
      edge_excl.erase({path2[ie2], path2[ie2 + 1]});
    }
    edge_excl.erase({path1[ie1], path1[ie1 + 1]});
  }

  return 0;
}

