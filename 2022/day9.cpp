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

  set<pair<int,int>> tail_visi;

  int Hx = 0, Hy = 0;
  int Tx = 0, Ty = 0;
  int ret = 1;
  tail_visi.insert({0,0});

  char dir;
  int moves;
  vector<char> alldirs;
  vector<int> allmoves;
  while(cin >> dir >> moves) {
    alldirs.push_back(dir);
    allmoves.push_back(moves);
    while(moves--) {
      if (dir == 'U') {
        Hy++;
      } else if (dir == 'D') {
        Hy--;
      } else if (dir == 'R') {
        Hx++;
      } else if (dir == 'L') {
        Hx--;
      }
      
      if (abs(Hx - Tx) >= 2 || abs(Hy - Ty) >= 2) {
        if (Hx > Tx)
          Tx++;
        else if (Hx < Tx)
          Tx--;

        if (Hy > Ty)
          Ty++;
        else if (Hy < Ty)
          Ty--;
        
        if (tail_visi.count({Tx,Ty}) == 0) {
          ret++;
          tail_visi.insert({Tx,Ty});
        }
      }
    }
  }

  cout << "Part A: " << ret << endl;

  // Part B
  tail_visi.clear();
  vector<pair<int,int>> coords(10,{0,0});

  map<char,pair<int,int>> movesmap = {
    {'U', {0,1}},
    {'D', {0,-1}},
    {'R', {1,0}},
    {'L', {-1,0}}
  };

  int ret2 = 0;
  for(int id = 0; id < alldirs.size(); ++id) {
    dir = alldirs[id];
    moves = allmoves[id];
    while(moves--) {
      coords[0].first += movesmap[dir].first;
      coords[0].second += movesmap[dir].second;

      for(int ikn = 0; ikn < coords.size() - 1; ++ikn) {
        const int& Hx = coords[ikn].first;
        const int& Hy = coords[ikn].second;
        int& Tx = coords[ikn+1].first;
        int& Ty = coords[ikn+1].second;
        if (abs(Hx - Tx) >= 2 || abs(Hy - Ty) >= 2) {
          if (Hx > Tx)
            Tx++;
          else if (Hx < Tx)
            Tx--;

          if (Hy > Ty)
            Ty++;
          else if (Hy < Ty)
            Ty--;
        }
      }

      if (tail_visi.count(coords.back()) == 0) {
        ret2++;
        tail_visi.insert(coords.back());
      }

      
    }
  }

  cout << "Part B: " << ret2 << endl;

  return 0;
}

