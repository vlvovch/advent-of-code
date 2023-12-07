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
  vector<int> copies(10000, 1);

  string tmp;
  cin >> tmp;
  int index = -1;
  while (true) {
    index++;
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
    for(int ind2 = index + 1; ind2 <= index + score; ind2++)
      copies[ind2] += copies[index];
    ret += copies[index];
  }

  cout << ret << endl;

  return 0;
}

