#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif


#define _CRT_SECURE_NO_WARNINGS
#define LOCAL

using namespace std;

vector<pair<int,int>> primeFactorization(int n) {
  vector<pair<int,int>> ret;
  for(int i = 2; i * i <= n; ++i) {
    if (n % i == 0) {
      int tcnt = 0;
      while(n % i == 0) {
        n /= i;
        tcnt++;
      }
      ret.push_back(make_pair(i, tcnt));
    }
  }
  if (n > 1)
    ret.push_back(make_pair(n, 1));
  return ret;
}

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

  vector<string> curs;
  for(auto& s : graph) {
    if (s.first[2] == 'A')
      curs.push_back(s.first);
  }
  vector<int> rets;
  for(auto& c : curs) {
    int ret = 0;
    while(c[2] != 'Z') {
      c = graph[c][LRdir[directions[ret%directions.size()]]];
      ret++;
    }
    rets.push_back(ret);
  }

  // Steps for each starting point
  for(auto& s : rets) {
    cout << s << " ";
    auto pfac = primeFactorization(s);
    for(auto& ss : pfac) {
      cout << ss.first << " " << ss.second << "  ";
    }
    cout << endl;
  }
  cout << endl;

  // Compute LCM of all steps
  map<int,int> lcm_factorize;
  for(auto& s : rets) {
    auto factors = primeFactorization(s);
    for(auto& f : factors) {
      lcm_factorize[f.first] = max(lcm_factorize[f.first], f.second);
    }
  }
  
  

  long long ret = 1;
  for(auto& s : lcm_factorize) {
    for(int i = 0; i < s.second; ++i) {
      ret *= s.first;
    }
  }

  cout << ret << endl;

  return 0;
}

