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
    cin.clear();
    tmp = "";
    cin >> tmp2 >> tmp;
    //cout << src.size() << endl;
  }

  auto transform_seeds = [&](const vector<long long>& seeds, const vector<vector<long long>>& map) {
    vector<long long> new_seeds;
    vector<long long> sources;

    for(auto el : map) {
      sources.push_back(el[0]);
    }

    for(int is = 0; is < seeds.size(); is += 2) {
      std::function<void(long long, long long, vector<long long>&)> process_seeds = [&](long long start, long long num, vector<long long>& new_seeds) {
        int pos = upper_bound(sources.begin(), sources.end(), start) - sources.begin();
        if (pos == 0) {
          new_seeds.push_back(start);
          if (start + num <= map[0][0]) {
            new_seeds.push_back(num);
          } else {
            new_seeds.push_back(map[0][0] - start);
            process_seeds(map[0][0], num - (map[0][0] - start), new_seeds);
          }
        } else {
          pos--;
          assert(map[pos][0] <= start);
          if (start < map[pos][0] + map[pos][2]) {
            long long new_start = map[pos][1] + start - map[pos][0];
            long long new_num = num;
            if (start + num > map[pos][0] + map[pos][2]) {
              new_num = map[pos][0] + map[pos][2] - start;
            }
            new_seeds.push_back(new_start);
            new_seeds.push_back(new_num);
            if (new_num != num) {
              process_seeds(map[pos][0] + map[pos][2], num - new_num, new_seeds);
            }
          } else {
            new_seeds.push_back(start);
            new_seeds.push_back(num);
          }
        }
      };

      process_seeds(seeds[is], seeds[is+1], new_seeds);
    }

    return new_seeds;
  };

  for(int stage = 0; stage < stages; ++stage) {
    seeds = transform_seeds(seeds, maps[stage]);
  }

  long long location = seeds[0];
  for(int is = 0; is < seeds.size(); is += 2) {
    location = min(location, seeds[is]);
  }

  cout << location << endl;

  return 0;
}

