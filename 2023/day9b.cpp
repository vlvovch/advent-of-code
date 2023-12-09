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

  vector<long long> final_vals;
  char cc[1000];
  while(cin.getline(cc, 1000)) {
    string s(cc);
    istringstream iss(s);
    vector<long long> vals;
    int val;
    while(iss >> val) {
      vals.push_back(val);
    }
    vector<vector<long long>> allvals;
    allvals.push_back(vals);
    bool allzero = false;
    while (!allzero) {
      vector<long long> next_vals;
      allzero = true;
      for(int i = 0; i < allvals.back().size() - 1; ++i) {
        next_vals.push_back(allvals.back()[i+1] - allvals.back()[i]);
        allzero &= (next_vals.back() == 0);
      }
      allvals.push_back(next_vals);
    }
    allvals.back().push_back(0);
    for(int i = allvals.size() - 2; i >= 0; --i) {
      allvals[i].push_back(allvals[i][0] - allvals[i+1].back());
    }
    final_vals.push_back(allvals[0].back());
    cout << allvals[0].back() << endl;
  }

  long long ret = 0;
  for(auto& v : final_vals) {
    ret += v;
  }

  cout << ret << endl;

  return 0;
}

