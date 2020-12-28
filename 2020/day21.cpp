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
  //freopen("day21.txt", "r", stdin);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  struct food {
    vstr ingr;
    vstr aller;
  };

  vector<food> foods;
  map<string,vector<vstr>> aller_to_ingr;

  char cc[1000];
  while (cin.getline(cc,1000)) {
    string tmp = string(cc);

    stringstream ss(tmp);
    int mode = 0;
    vstr ingrs, allers;
    while (ss >> tmp) {
      if (tmp == "(contains") {
        mode = 1;
        continue;
      }

      if (mode == 0) {
        ingrs.push_back(tmp);
        continue;
      } else {
        allers.push_back(tmp.substr(0,tmp.size()-1));
        continue;
      }
    }

    foods.push_back({ingrs, allers});

    trav(aller,allers) {
      aller_to_ingr[aller].push_back(ingrs);
    }
  }

  set<string> ingr_ident;
  set<string> aller_ident;

  auto clear_ingr = [&](string ingr) {
    trav(aller,aller_to_ingr) {
      trav(ings,aller.second) {
        rep(i,ings.size()) {
          if (ings[i] == ingr) {
            ings.erase(ings.begin() + i);
            i--;
          }
        }
      }
    }
  };

  vector<pair<string,string>> themap;

  rep(iters,aller_to_ingr.size()) {
    trav(aller,aller_to_ingr) {
      string allername = aller.first;
      if (aller_ident.count(allername))
        continue;

      //cout << allername << endl;
      
      map<string,int> cntocc;
      trav(allerlist,aller.second) {
        trav(ingr,allerlist) {
          //cout << ingr << " ";
          cntocc[ingr]++;
        }
        //cout << endl;
      }

      int cntcand = 0;
      string ingrname;
      trav(ingr,cntocc) {
        if (ingr.second == aller.second.size()) {
          cntcand++;
          ingrname = ingr.first;
        }
      }
      if (cntcand == 1) {
        aller_ident.insert(allername);
        ingr_ident.insert(ingrname);
        //cout << allername << " " << ingrname << endl;
        themap.push_back({allername,ingrname});
        clear_ingr(ingrname);
        break;
      }
    }
  }

  ll ret = 0;
  trav(el,foods) {
    trav(ingr,el.ingr)
      if (ingr_ident.count(ingr)==0)
        ret++;
  }

  cout << "Part 1 answer: " << ret << endl;

  sort(all(themap));
  string ans = "";
  trav(el,themap)
    ans += el.second + ",";
  
  ans = ans.substr(0,ans.size()-1);
  cout << "Part 2 answer: " << ans << endl;

  return 0;
}

