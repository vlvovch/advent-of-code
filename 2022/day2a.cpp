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

  int ret = 0;
  
  char Opp, Me;

  while (cin >> Opp >> Me) {
    ret += pts[Me-'X'][Opp - 'A'];
    ret += 1 + (int)(Me - 'X');
  }

  cout << ret << endl;

  return 0;
}

