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

  vstr inigrid;
  string tmp;
  while (cin >> tmp)
    inigrid.push_back(tmp);
  
  int dimx = inigrid[0].size() + 2 * 6;
  int offx = 6;
  int dimy = inigrid.size() + 2 * 6;
  int offy = 6;
  int dimz = 13;
  int offz = 6;
  int dimw = 13;
  int offw = 6;

  vector<vector<vector<vector<char>>>> grid;
  grid.resize(dimx);
  rep(ix,dimx) {
    grid[ix].resize(dimy);
    rep(iy,dimy) {
      grid[ix][iy].resize(dimz);
      rep(iz,dimz) {
        grid[ix][iy][iz] = vector<char>(dimw, '.');
      }
    }
  }

  rep(ix,inigrid[0].size()) {
    rep(iy,inigrid.size())
      grid[offx+ix][offy+iy][offz][offw] = inigrid[iy][ix];
  }

  int cycles = 6;
  while(cycles--) {
    vector<vector<vector<vector<char>>>> ngrid = grid;
    for(int ix = 0; ix < dimx; ix++) {
      for(int iy = 0; iy < dimy; iy++) {
        for(int iz = 0; iz < dimz; iz++) {
          for(int iw = 0; iw < dimw; iw++) {
            char cval = grid[ix][iy][iz][iw];

            int cntactive = 0;

            for(int dx = -1; dx <= 1; dx++)
              for(int dy = -1; dy <= 1; dy++)
                for(int dz = -1; dz <= 1; dz++) 
                  for(int dw = -1; dw <= 1; dw++) {
                    if (dx == 0 && dy == 0 && dz == 0 && dw == 0)
                      continue;

                    if (ix + dx < 0 || ix + dx >= dimx)
                      continue;
                    if (iy + dy < 0 || iy + dy >= dimy)
                      continue;
                    if (iz + dz < 0 || iz + dz >= dimz)
                      continue;
                    if (iw + dw < 0 || iw + dw >= dimw)
                      continue;
                    
                    cntactive += (grid[ix+dx][iy+dy][iz+dz][iw+dw] == '#');
                }
            
            ngrid[ix][iy][iz][iw] = '.';
            if (cntactive == 3 || (cval == '#' && cntactive == 2))
              ngrid[ix][iy][iz][iw] = '#';
          }
        }
      }
    }

    grid = ngrid;
  }

  int ret = 0;
  for(int ix = 0; ix < dimx; ix++) {
    for(int iy = 0; iy < dimy; iy++) {
      for(int iz = 0; iz < dimz; iz++) {
        for(int iw = 0; iw < dimw; iw++) {
          char cval = grid[ix][iy][iz][iw];
          ret += (cval == '#');
        }
      }
    }
  }

  cout << ret << endl;

  return 0;
}

