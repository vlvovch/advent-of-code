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
  //freopen("day13.txt", "r", stdin);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  int timestamp;
  cin >> timestamp;

  string tmp;
  cin >> tmp;
  vi buses;

  int ind = 0;
  string tmp2;
  while (ind < tmp.size()) {
    if (tmp[ind] != ',') {
      tmp2 += tmp[ind];
    } else {
      if (tmp2 != "x") {
        int tID = atoi(tmp2.c_str());
        buses.push_back(tID);
      }
      tmp2 = "";
    }
    ind++;
  }

  sort(all(buses));

  int mint = buses[0];
  int id = -1;

  rep(ib,buses.size()) {
    int tdel = timestamp % buses[ib];
    if (tdel != 0)
      tdel = buses[ib] - tdel;
    
    if (id == -1 || tdel < mint) {
      mint = tdel;
      id = ib;
    }
  }

  cout << mint * buses[id] << endl;

  return 0;
}

