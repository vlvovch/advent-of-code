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

  string mask;

  map<int,ll> mem;

  string tmp1, tmp2, tmp3;
  while (cin >> tmp1 >> tmp2 >> tmp3) {
    if (tmp1 == "mask") {
      mask = tmp3;
    }
    else {
      assert(tmp1.substr(0,3) == "mem");

      int pos = atoi( tmp1.substr(4, tmp1.size() - 5).c_str());

      ll nval0 = atoi(tmp3.c_str());
      string sval = "";

      rep(ibit,36) {
        sval += '0' + (nval0%2);
        nval0 /= 2;
      }

      reverse(all(sval));

      // cout << sval << endl;

      ll nval = 0;
      rep(ibit,36) {
        nval *= 2;
        if (mask[ibit] == 'X')
          nval += (ll)(sval[ibit] - '0');
        else {
          nval += (ll)(mask[ibit] - '0');
        }
      }

      // cout << nval << endl;

      mem[pos] = nval;
    }
  }

  ll ret = 0;
  trav(el,mem)
    ret += el.second;

  cout << ret << endl;

  return 0;
}

