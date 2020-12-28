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
  //freopen("day11.txt", "r", stdin);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  vstr grid;
  string tmp;
  while(cin >> tmp) {
    grid.push_back(tmp);
  }
  int maxx = grid.size();
  int maxy = grid[0].size();

  int cycles = 0;
  while (1) {
    cycles++;

    int cntchange = 0;
    
    vstr ngrid = grid;
    rep(ix,maxx) {
      rep(iy,maxy) {
        if (grid[ix][iy] == '.')
          continue;
        int cntoccup = 0;
        vii dirs = { {1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}};
        rep(id,dirs.size()) {
          int cx = ix;
          int cy = iy;
          cx += dirs[id][0];
          cy += dirs[id][1];
          while (cx >= 0 && cx < maxx && cy >= 0 && cy < maxy) {
            if (grid[cx][cy] == '#') {
              cntoccup++;
              break;
            } else if (grid[cx][cy] == 'L') {
              break;
            }

            cx += dirs[id][0];
            cy += dirs[id][1];
          }
        }
        
        if (grid[ix][iy] == 'L' && cntoccup == 0)
          ngrid[ix][iy] = '#', cntchange++;
        else if (grid[ix][iy] == '#' && cntoccup >= 5)
          ngrid[ix][iy] = 'L', cntchange++;
      }
    }
    grid = ngrid;
    if (cntchange == 0)
      break;
  }

  cout << cycles << " cycles" << endl;

  int ret = 0;
  rep(ix,maxx)
      rep(iy,maxy)
        ret += grid[ix][iy] == '#';
  
  cout << ret << endl;

  return 0;
}

