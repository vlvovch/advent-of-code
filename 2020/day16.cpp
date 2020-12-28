#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<pii> vpii;
typedef vector<string> vstr;
template <class T> int size(const T& x) { return x.size(); }
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() 
// const int INF = 2147483647;
#define FOR(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define rep(i,n) for(int i=0;i<n;i++)
#define trav(a,x) for (auto&& a: x)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#define LOCAL
#endif

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

  vpii ranges;

  char cc[1000];
  int mode = 0;
  ll ret = 0;
  while (cin.getline(cc,1000)) {
    string tmp = string(cc);

    if (tmp == "")
      continue;

    stringstream ss(tmp);


    ss >> tmp;

    if (mode == 0) {
      string tmp2;
      while (tmp.back() != ':') {
        ss >> tmp2;
        tmp += " " + tmp2;
      }
      if (tmp == "your ticket:") {
        mode = 1;
        continue;
      }

      //cout << tmp << endl;
      //assert(tmp.back() == ':');

      string rang;
      

      while(ss >> rang) {
        string tnum = "";
        int ind = -1;
        int n1 = 0, n2 = 0;
        while (++ind < rang.size()) {
          if (rang[ind] == '-') {
            n1 = atoi(tnum.c_str());
            tnum = "";
          } else {
            tnum += rang[ind];
          }
        }
        n2 = atoi(tnum.c_str());

        ranges.push_back({n1,n2});
        
        if (!(ss >> rang))
          break;
        else {
          assert(rang == "or");
        }
      }
    }

    // your ticket
    if (mode == 1) {
      cin.getline(cc,1000);
      mode = 2;
    }

    auto check_valid = [&](int num) {
      trav(rng,ranges) {
        if (num >= rng.first && num <= rng.second)
          return true;
      }
      return false;
    };

    // nearby tickets
    if (mode == 2) {
      string inp = string(cc);
      vi ns;
      int ind = 0;
      string tnum = "";
      while (ind < inp.size()) {
        if (inp[ind] == ',') {
          ns.push_back(atoi(tnum.c_str()));
          tnum = "";
        } else {
          tnum += inp[ind];
        }
        ind++;
      }
      if (tnum != "")
          ns.push_back(atoi(tnum.c_str()));

      trav(n,ns) {
        if (!check_valid(n))
          ret += n;
      }
    }

  }

  cout << ret << endl;

  return 0;
}

