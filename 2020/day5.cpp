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

  int ret = 0;
  string bpass;

  vi ids;

  while (cin >> bpass) {
    //cout << bpass << " ";

    int row = 0;
    rep(i,7) {
      row *= 2;
      if (bpass[i] == 'B')
        row++;
    }
    int col = 0;
    rep(i,3) {
      col *= 2;
      if (bpass[7+i] == 'R')
        col++;
    }

    int ID = row * 8 + col;
    //cout << ID << endl;

    ret = max(ret, ID);

    ids.push_back(ID);
  }

  cout << "Highest seat ID: " << ret << endl;

  // second part

  sort(all(ids));
  rep(i,ids.size() - 1) {
    if (ids[i] + 2 == ids[i+1]) {
      cout << "Your seat ID: " << ids[i] + 1 << endl;
    }
  }

  return 0;
}

