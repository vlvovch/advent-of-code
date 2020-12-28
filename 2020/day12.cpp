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

  vii dirs = {{1,0}, {0,-1}, {-1,0}, {0,1}};

  std::map<char,int> mapdir = { {'E', 0}, {'S',1}, {'W',2}, {'N',3} };

  int cdir = 0;

  int cx = 0, cy = 0;

  string ncmd;
  while(cin >> ncmd) {
    int numb = atoi(ncmd.substr(1).c_str());
    char cmd = ncmd[0];

    if (mapdir.count(cmd)) {
      int dirmv = mapdir[cmd];
      cx += dirs[dirmv][0] * numb;
      cy += dirs[dirmv][1] * numb;
    }
    else if (cmd == 'F') {
      cx += dirs[cdir][0] * numb;
      cy += dirs[cdir][1] * numb;
    }
    else {
      if (numb == 180) {
        cdir = (cdir + 2)%4;
      }
      else {
        if (numb == 270) {
          numb = 90;
          if (cmd == 'R')
            cmd = 'L';
          else
            cmd = 'R';
        }
        assert(numb == 90);
        if (cmd == 'R') {
          cdir = (cdir + 1)%4;
        }
        else
        {
          cdir = (cdir - 1 + 4)%4;
        }
        
      }
    }
  }

  cout << abs(cx) + abs(cy) << endl;

  return 0;
}

