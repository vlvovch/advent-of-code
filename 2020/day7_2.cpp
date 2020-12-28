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
//freopen("day7.txt", "r", stdin);
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  map<string, vector<pair<string,int>>> g;

  char cc[1000];
  while (cin.getline(cc,1000)) {
    string typ, col, tmp;
    tmp = string(cc);
    if (tmp.size() == 0)
      continue;
    stringstream ss(tmp);

    ss >> typ >> col >> tmp;
    
    ss >> tmp;

    while (1) {
      string typ2, col2;
      ss >> tmp;
      ss >> typ2;
      ss >> col2;

      if (tmp == "no")
        break;

      int num = atoi(tmp.c_str());

      ss >> tmp;

      g[typ + " " + col].push_back({typ2 + " " + col2,num});

      if (tmp.back() == '.')
        break;
    }

  }

  int ret = 0;
  queue<pair<string,int>> q;
  q.push({"shiny gold", 1});

  while (!q.empty()) {
    auto el = q.front(); q.pop();
    trav(nel,g[el.first]) {
      ret += el.second * nel.second;
      q.push({nel.first, el.second * nel.second});
    }
  }

  cout << ret << endl;

  return 0;
}

