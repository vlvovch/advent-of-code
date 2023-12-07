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

  vector<long long> times, dists;
  char cc[1000];
  cin.getline(cc, 1000);
  string timestr = string(cc);
  cin.getline(cc, 1000);
  string diststr = string(cc);

  {
    stringstream iss;
    iss << timestr;
    string tmp;
    iss >> tmp;
    assert(tmp == "Time:");
    long long val;
    while (iss >> val) {
      times.push_back(val);
    }
  }

  {
    stringstream iss;
    iss << diststr;
    string tmp;
    iss >> tmp;
    assert(tmp == "Distance:");
    long long val;
    while (iss >> val) {
      dists.push_back(val);
    }
  }

  assert(times.size() == dists.size());

  int races = times.size();

  long long ret = 1;
  for(int race = 0; race < races; race++) {
    long long wins = 0;
    for(long long speed = 0; speed <= times[race]; ++speed) {
      long long dist = speed * (times[race] - speed);
      if (dist > dists[race])
        wins++;
    }
    ret *= wins;
  }

  cout << ret << endl;

  return 0;
}

