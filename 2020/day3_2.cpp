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

  vstr fld;
  string tmp;
  while (cin >> tmp) {
    fld.push_back(tmp);
  }

  int M = fld[0].size();
  int N = fld.size();

  long long ret = 1;
  vpii dirs = {{1,1}, {3,1}, {5,1}, {7,1}, {1,2}};
  vector<ll> trets(dirs.size(), 0);


  rep(i,dirs.size()) {
    int r = 0, c = 0;
    while (1) {
      c += dirs[i].first;
      c %= M;
      r += dirs[i].second;
      if (r >= N)
        break;
      
      trets[i] += (fld[r][c] == '#');
    }

    ret *= trets[i];
  }
  cout << ret << endl;

  return 0;
}

