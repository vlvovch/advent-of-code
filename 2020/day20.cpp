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
  //freopen("day20.txt", "r", stdin);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  vi inds;
  vector<vstr> tiles;

  {
    string tmp1, tmp2;
    while (cin >> tmp1 >> tmp2) {
      int tind = atoi(tmp2.substr(0,tmp2.size()-1).c_str());
      inds.push_back(tind);

      tiles.push_back(vstr());
      rep(i,10) {
        cin >> tmp1;
        tiles.back().push_back(tmp1);
      }
    }
  }

  //cout << tiles.size() << " " << round(sqrt(tiles.size())) << endl;
  int sidelength = round(sqrt(tiles.size()));

  auto get_edges = [&](vstr& tile) {
    vstr ret;
    ret.push_back(tile[0]);
    string tmp = "";
    rep(i,tile.size()) {
      tmp += tile[i][tile[0].size()-1];
    }
    ret.push_back(tmp);
    ret.push_back(tile.back());
    tmp = "";
    rep(i,tile.size()) {
      tmp += tile[i][0];
    }
    ret.push_back(tmp);
    return ret;
  };

  struct matched_edge {
    int ind, edge, flip;
  };

  auto match_edge = [&](int ind, int iedge) {
    matched_edge ret = {-1, 0, 0};

    auto edge1 = get_edges(tiles[ind])[iedge];
    
    rep(itile,tiles.size()) {
      if (itile == ind)
        continue;

      auto edges2 = get_edges(tiles[itile]);
      rep(i2,edges2.size()) {
        auto edge2 = edges2[i2];
        if (edge1 == edge2) {
          ret = {itile, i2, 0};
          return ret;
        }
        reverse(all(edge2));
        if (edge1 == edge2) {
          ret = {itile, i2, 1};
          return ret;
        }
      }
    }

    return ret;
  };

  auto edges_match = [&](int ind) {
    auto edges = get_edges(tiles[ind]);
    int ret = 0;

    trav(edge,edges) {
      bool fl = false;
      int tcnt = 0;
      rep(itile,tiles.size()) {
        if (itile == ind)
          continue;
        auto edges2 = get_edges(tiles[itile]);

        bool tfl = false;
        trav(edge2,edges2) {
          fl  |= (edge == edge2);
          tfl |= (edge == edge2);
          reverse(all(edge2));
          fl |= (edge == edge2);
          tfl |= (edge == edge2);
        }

        if (tfl)
          tcnt++;

        //if (fl)
        //  break;
      }
      if (fl) ret++;
    }
    return ret;
  };

  // rep(i,tiles.size())
  //   cout << inds[i] << " " << edges_match(i) << endl;
  
  ll ret = 1;
  rep(i,tiles.size())
    if (edges_match(i) == 2)
      ret *= inds[i];

  cout << "Part 1 answer: " << ret << endl;

  auto rotate_tile = [&](vstr& tile, int clockwise) {
    vstr ret = tile;
    if (clockwise) {
      rep(r,tile.size()) {
        rep(c,tile[0].size()) {
          ret[c][tile.size()-1-r] = tile[r][c];
        }
      }
    } else {
      rep(r,tile.size()) {
        rep(c,tile[0].size()) {
          ret[tile.size()-1-c][r] = tile[r][c];
        }
      }
    }
    return ret;
  };

  auto flip_tile = [&](vstr& tile, int dirx) {
    vstr ret = tile;
    if (dirx) {
      rep(r,tile.size()) {
        rep(c,tile[0].size()/2) {
          swap(ret[r][c], ret[r][tile[0].size() - 1 - c]);
        }
      }
    } else {
      rep(c,tile[0].size()) {
        rep(r,tile.size()/2) {
          swap(ret[r][c], ret[tile.size() - 1 - r][c]);
        }
      }
    }
    return ret;
  };

  int itopleft = -1;
  {
    rep(i,tiles.size()) {
      if (edges_match(i) == 2) {
        itopleft = i;
        break;
      }
    }
    //cout << "Top left: " << itopleft << endl;
  }

  rep(ii,2)
  {
    int b1 = -1, b2 = -1;
    rep(i,4) {
      if (match_edge(itopleft,i).ind == -1) {
        if (b1 == -1)
          b1 = i;
        else
          b2 = i;
      }
    }
    
    //cout << b1 << " " << b2 << endl;

    if (b1 == 0 && b2 == 1)
      tiles[itopleft] = rotate_tile(tiles[itopleft], 0);
    if (b1 == 1 && b2 == 2) {
      tiles[itopleft] = rotate_tile(tiles[itopleft], 0);
      tiles[itopleft] = rotate_tile(tiles[itopleft], 0);
    }
    if (b1 == 2 && b2 == 3)
      tiles[itopleft] = rotate_tile(tiles[itopleft], 1);
  }

  vii maptiles(sidelength, vi(sidelength, -1));
  maptiles[0][0] = itopleft;
  vi tilesused(tiles.size(), 0);
  tilesused[itopleft] = 1;

  vstr grid;
  rep(r,sidelength) {
    rep(c,sidelength) {
      if (c == 0) {
        // first the leftmost tile, match 0 to prev 2
        if (r == 0) 
          continue;
        
        vstr& tileprev = tiles[maptiles[r - 1][c]];
        auto edgeprev = get_edges(tileprev)[2];

        auto matched_edge = match_edge(maptiles[r - 1][c], 2);

        int ind2 = matched_edge.ind, edge2 = matched_edge.edge, flip2 = matched_edge.flip;
        //cout << r << " " << c << " " << ind2 << endl;

        if (edge2 == 0) {
          if (flip2)
            tiles[ind2] = flip_tile(tiles[ind2], 1);
        } else if (edge2 == 1) {
          tiles[ind2] = rotate_tile(tiles[ind2], 0);
          if (flip2)
            tiles[ind2] = flip_tile(tiles[ind2], 1);
        } else if (edge2 == 2) {
          tiles[ind2] = rotate_tile(tiles[ind2], 0);
          tiles[ind2] = rotate_tile(tiles[ind2], 0);
          if (!flip2)
            tiles[ind2] = flip_tile(tiles[ind2], 1);
        } else if (edge2 == 3) {
          tiles[ind2] = rotate_tile(tiles[ind2], 1);
          if (!flip2)
            tiles[ind2] = flip_tile(tiles[ind2], 1);
        }

        maptiles[r][c] = ind2;
        //assert(tilesused[ind2] == 0);
        tilesused[ind2] = 1;

      } else {
        // all other tiles in row, match 3 to prev 1
        vstr& tileprev = tiles[maptiles[r][c-1]];
        auto edgeprev = get_edges(tileprev)[1];

        auto matched_edge = match_edge(maptiles[r][c-1], 1);

        int ind2 = matched_edge.ind, edge2 = matched_edge.edge, flip2 = matched_edge.flip;

        // cout << r << " " << c << " " << ind2 << " " << edge2 << endl;

        //if (0)
        if (edge2 == 0) {
          tiles[ind2] = rotate_tile(tiles[ind2], 0);
          if (!flip2)
            tiles[ind2] = flip_tile(tiles[ind2], 0);
        } else if (edge2 == 1) {
          tiles[ind2] = rotate_tile(tiles[ind2], 0);
          tiles[ind2] = rotate_tile(tiles[ind2], 0);
          if (!flip2)
            tiles[ind2] = flip_tile(tiles[ind2], 0);
        } else if (edge2 == 2) {
          tiles[ind2] = rotate_tile(tiles[ind2], 1);
          if (flip2)
            tiles[ind2] = flip_tile(tiles[ind2], 0);
        } else if (edge2 == 3) {
          if (flip2)
            tiles[ind2] = flip_tile(tiles[ind2], 0);
        }

        maptiles[r][c] = ind2;
        //assert(tilesused[ind2] == 0);
        tilesused[ind2] = 1;
      }
    }
    rep(rr,tiles[0].size()) {
      if (rr == 0 || rr == tiles[0].size()-1)
        continue;
      grid.push_back("");
      rep(cc,sidelength) {
        //cout << tiles[maptiles[r][cc]][rr];
        //grid.back() += tiles[maptiles[r][cc]][rr];
        grid.back() += tiles[maptiles[r][cc]][rr].substr(1, tiles[0].size()-2);
        //grid.back() += " ";
        //cout << " ";
      }
      //cout << endl;
    }
    //cout << endl;
  }

  // grid = rotate_tile(grid, 0);
  // grid = flip_tile(grid, 0);
  
  // trav(el,grid)
  //   cout << el << endl;

  // rep(r,sidelength) {
  //   rep(c,sidelength)
  //     cout << maptiles[r][c] << " ";
  //   cout << endl;
  //}
  ll cntsh = 0;
  trav(el,grid)
    trav(el2,el)
      cntsh += (el2 == '#');

  vstr sea_monster;
  sea_monster.push_back("                  # ");
  sea_monster.push_back("#    ##    ##    ###");
  sea_monster.push_back(" #  #  #  #  #  #   ");

  auto check_monster_match = [&](vstr& cand) {
    assert(cand.size() == 3);

    bool fl = true;
    rep(r,sea_monster.size()) {
      assert(cand[r].size() == sea_monster[r].size());
      rep(c,sea_monster[r].size()) {
        if (sea_monster[r][c] == '#')
          fl &= (cand[r][c] == '#');
      }
    }
    return fl;
  };

  // grid = rotate_tile(grid, 0);
  // grid = flip_tile(grid, 0);
  // grid = rotate_tile(grid, 1);  
  // grid = flip_tile(grid, 1);

  ret = 0;
  rep(rot, 4) {
    rep(flipx, 2) {
      rep(flipy, 2) {
        vstr ngrid = grid;
        rep(i,rot)
          ngrid = rotate_tile(ngrid, 1);
        if (flipx)
          ngrid = flip_tile(ngrid, 1);
        if (flipy)
          ngrid = flip_tile(ngrid, 0);

        int n_monsters = 0;

        rep(r,ngrid.size() - sea_monster.size() + 1) {
          rep(c,ngrid.size() - sea_monster[0].size() + 1) {
            vstr cand;
            rep(rmo,sea_monster.size())
              cand.push_back(ngrid[r+rmo].substr(c, sea_monster[rmo].size()));
            
            if (check_monster_match(cand))
              n_monsters++;
          }
        }

        //cout << n_monsters << endl;
        if (n_monsters) {
          ret = cntsh - n_monsters * 15;
          //cout << "ret: " << ret << endl;
        }
      }
    }
  }

  cout << "Part 2 answer: " << ret << endl;

  return 0;
}

