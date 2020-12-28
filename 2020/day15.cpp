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
  //freopen("day15.txt", "r", stdin);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  vi ns;
  string inp;
  cin >> inp;

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

  
  // vi spoken = ns;
  // for(int turn = ns.size() + 1; turn <= 2020; turn++) {
  //   int im = ns.size() - 2;
  //   while (im >= 0 && ns[im] != ns.back())
  //     im--;
    
  //   if (im >= 0)
  //     ns.push_back(ns.size() - 1 - im);
  //   else
  //     ns.push_back(0);
  // }

  // cout << ns.back() << endl;


  map<int,int> spokelast, spoke_secondlast;

  for(int turn = 1; turn <= ns.size(); ++turn) {
    int ti = turn - 1;
    spokelast[ns[ti]] = turn;
  }

  int lastspoken = ns.back();
  for(int turn = ns.size() + 1; turn <= 30000000; turn++) {
    if (spoke_secondlast.count(lastspoken) == 0) {
      lastspoken = 0;
    } else {
      lastspoken = spokelast[lastspoken] - spoke_secondlast[lastspoken];
    }

    if (spokelast.count(lastspoken) == 0) {
      spokelast[lastspoken] = turn;
    } else {
      spoke_secondlast[lastspoken] = spokelast[lastspoken];
      spokelast[lastspoken] = turn;
    }
    if (turn == 2020)
      cout << "2020th number spoken: " << lastspoken << endl;
  }

  cout << "30000000th number spoken: " << lastspoken << endl;

  return 0;
}

