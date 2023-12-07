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

  // Rock, paper, scissors
  vector<vector<int>> pts = {
    {3, 0, 6},
    {6, 3, 0},
    {0, 6, 3}
  };

  map<char,int> outcome = {{'X',0}, {'Y',3}, {'Z',6}};

  int ret = 0;
  
  char Opp, Res, Me;

  while (cin >> Opp >> Res) {
    ret += outcome[Res];

    for(int i = 0; i < 3; ++i)
      if (pts[i][Opp - 'A'] == outcome[Res])
        Me = 'A' + i;
      
    ret += 1 + (int)(Me - 'A');
  }

  cout << ret << endl;

  return 0;
}

