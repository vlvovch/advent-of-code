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

  string rucksack;
  while (cin >> rucksack) {
    char item = '0';
    set<char> itemsA;
    int sz = rucksack.size() / 2;
    for(int i = 0; i < sz; ++i) {
      itemsA.insert(rucksack[i]);
    }
    for(int i = 0; i < sz; ++i) {
      if (itemsA.count(rucksack[i + sz]) > 0) {
        item = rucksack[i + sz];
        break;
      }
    }
    if (item >= 'a' && item <= 'z')
      ret += 1 + (item - 'a');
    else
      ret += 27 + (item - 'A');
  }

  cout << ret << endl;

  return 0;
}

