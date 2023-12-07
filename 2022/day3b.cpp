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

  vector<string> rucksacks;
  string rucksack;
  while (cin >> rucksack) {
    rucksacks.push_back(rucksack);
  }



  int ret = 0;
  int N = rucksacks.size();
  vector<int> used(N, 0);
  vector<char> items;
  for(int i1 = 0; i1 < N; ++i1) {
    if (used[i1]) continue;
    set<int> s1;
    for(char c : rucksacks[i1]) {
      s1.insert(c);
    }
    for(int i2 = i1 + 1; i2 < N; ++i2) {
      if (used[i2]) continue;
      set<int> s2;
      for(char c : rucksacks[i2]) {
        if (s1.count(c) > 0) {
          s2.insert(c);
        }
      }
      for(int i3 = i2 + 1; i3 < N; ++i3) {
        for(char c : rucksacks[i3]) {
          if (s2.count(c) > 0) {
            used[i1] = 1;
            used[i2] = 1;
            used[i3] = 1;
            items.push_back(c);
            cout << i1 << " " << i2 << " " << i3 << " " << c << endl;
            break;
          }
        }
        if (used[i3])
          break;
      }
      if (used[i2])
        break;
    }
  }

  for(auto item : items) {
    if (item >= 'a' && item <= 'z')
      ret += 1 + (item - 'a');
    else
      ret += 27 + (item - 'A');
  }

  cout << ret << endl;

  return 0;
}

