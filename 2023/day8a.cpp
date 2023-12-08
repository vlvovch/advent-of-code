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

  string directions;
  map<char,int> LRdir = {{'L', 0}, {'R', 1}};

  cin >> directions;

  map<string,vector<string>> graph;
  string cur, tmp, left, right;
  while (cin >> cur >> tmp >> left >> right) {
    assert(left.size() == 5);
    left = left.substr(1, left.size() - 2);
    assert(right.size() == 4);
    right = right.substr(0, right.size() - 1);
    graph[cur] = {left, right};
  }

  cur = "AAA";
  int ret = 0;
  while(cur != "ZZZ") {
    cur = graph[cur][LRdir[directions[ret%directions.size()]]];
    ret++;
  }

  cout << ret << endl;

  return 0;
}

