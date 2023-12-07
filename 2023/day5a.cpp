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
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  int stages = 0;
  vector<long long> seeds;
  vector< vector< vector<long long> > > maps;
  vector< vector<long long> > sources;

  string tmp, tmp2;
  cin >> tmp;
  {
    long long seed;
    while (cin >> seed) {
      seeds.push_back(seed);
    }
    cin.clear();
  }


  cin >> tmp2 >> tmp;
  //cout << tmp << endl;
  while (tmp == "map:") {
    stages++;
    long long dest, source, val;
    vector< vector<long long> > map;
    while (cin >> dest >> source >> val) {
      //cout << dest << " " << source << " " << val << endl;
      map.push_back({source, dest, val});
    }
    sort(map.begin(), map.end());
    maps.push_back(map);
    vector<long long> src;
    for(auto el : map) {
      src.push_back(el[0]);
    }
    sources.push_back(src);
    cin.clear();
    tmp = "";
    cin >> tmp2 >> tmp;
    //cout << src.size() << endl;
  }

  long long location = -1;

  for(long long seed : seeds) {
    long long val = seed;
    for(int stage = 0; stage < stages; ++stage) {
      int pos = upper_bound(sources[stage].begin(), sources[stage].end(), val) - sources[stage].begin();
      if (pos == 0) {
        val = val;
      } else {
        pos--;
        // cout << sources[stage][pos] << " " << val << endl;
        assert(maps[stage][pos][0] <= val);
        if (val < maps[stage][pos][0] + maps[stage][pos][2]) {
          val = maps[stage][pos][1] + val - maps[stage][pos][0];
        } else {
          val = val;
        }
      }
    }
    cout << val << endl;
    if (location == -1 || val < location)
      location = val;
  }

  cout << location << endl;

  return 0;
}

