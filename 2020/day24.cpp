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

  map<string,vi> dirs;
  dirs["e"]  = {1, 0};
  dirs["se"] = {1, -1};
  dirs["sw"] = {0, -1};
  dirs["w"]  = {-1, 0};
  dirs["nw"] = {-1, 1};
  dirs["ne"] = {0, 1};

  set<pii> flipped;

  string cmd;
  while (cin >> cmd) {
    int ind = 0;
    int cx = 0, cy = 0;
    while (ind < cmd.size()) {
      string dir = "";
      dir += cmd[ind];
      if (dir == "n" || dir == "s") {
        ind++;
        dir += cmd[ind];
      }

      cx += dirs[dir][0];
      cy += dirs[dir][1];

      ind++;
    }
    

    if (flipped.count({cx,cy})) {
      flipped.erase({cx,cy});
    } else {
      flipped.insert({cx,cy});
    }
  }

  cout << "Part 1 answer: " << flipped.size() << endl;

  int maxx = 0, minx = 0, maxy = 0, miny = 0;
  trav(el,flipped) {
    maxx = max(maxx, el.first);
    minx = min(minx, el.first);
    maxy = max(maxy, el.second);
    miny = min(miny, el.second);
  }

  minx -= 101;
  maxx += 101;
  miny -= 101;
  maxy += 101;
  vii grid(maxx-minx+1, vi(maxy-miny+1, 0));
  trav(el,flipped) {
    grid[el.first - minx][el.second - miny] = 1;
  }

  int days = 100;
  int nblack = 0;
  while (days--) {
    vii ngrid = grid;

    nblack = 0;

    rep(x,grid.size()) {
      rep(y,grid[0].size()) {
        int cntblack = 0;
        trav(dir,dirs) {
          int nx = x + dir.second[0];
          int ny = y + dir.second[1];
          if (nx < 0 || nx >= grid.size())
            continue;
          if (ny < 0 || ny >= grid[0].size())
            continue;
          
          cntblack += grid[nx][ny];
        }
        if (ngrid[x][y]) {
          if (cntblack == 0 || cntblack > 2)
            ngrid[x][y] = 0;
        } else if (ngrid[x][y] == 0) {
          if (cntblack == 2)
            ngrid[x][y] = 1;
        }

        if (ngrid[x][y])
          nblack++;
      }
    }

    //cout << "Day " << 100 - days << ": " << nblack << endl;

    grid = ngrid;
  }

  cout << "Part 2 answer: " << nblack << endl;

  return 0;
}

