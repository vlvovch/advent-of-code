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

  int ret = 0;

  string tmp;
  cin >> tmp;
  while (true) {
    if (tmp != "Card")
      break;
    cin >> tmp >> tmp;
    set<int> winning;
    int score = 0;
    while (tmp != "|") {
      winning.insert(stoi(tmp));
      cin >> tmp;
    }
    while (cin >> tmp && tmp != "Card") {
      if (winning.count(stoi(tmp)) > 0)
        score++;
    }
    if (score > 0)
      ret += (1 << (score - 1));
  }

  cout << ret << endl;

  return 0;
}

