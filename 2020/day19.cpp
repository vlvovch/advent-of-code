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
  //freopen("day19.txt", "r", stdin);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  map<int,vii> rules;
  int inda, indb;

  char cc[1000];
  int mode = 0;
  vstr msg;
  int maxrules = 0;
  while (cin.getline(cc,1000)) {
    string tmp = string(cc);
    if (tmp == "") {
      mode = 1;
    }

    if (mode == 0) {
      stringstream ss(tmp);

      ss >> tmp;
      int ind = atoi(tmp.substr(0, tmp.size() - 1).c_str());
      vi rl;
      ss >> tmp;
      maxrules = max(maxrules, ind);
      if (tmp == "\"a\"") {
        inda = ind;
        continue;
      } else if (tmp == "\"b\"") {
        indb = ind;
        continue;
      }

      rl.push_back(atoi(tmp.c_str()));
      while (ss >> tmp) {
        if (tmp == "|") {
          rules[ind].push_back(rl);
          rl.clear();
        } else {
          rl.push_back(atoi(tmp.c_str()));
        }
      }
      if (rl.size())
        rules[ind].push_back(rl);
    } else {
      if (tmp != "")
        msg.push_back(tmp);
    }
  }


  

  std::function<vstr(vstr&,vstr&)> merger = [&](vstr& a, vstr& b) {
    vstr ret;
    trav(el1,a)
      trav(el2,b)
        ret.push_back(el1 + el2);
    return ret;
  };

  vector<vstr> matches(maxrules + 1);
  int depth = 0;
  std::function<vstr(int)> go_dp = [&](int rl) {
    if (rl == inda)
      return vstr(1,"a");
    else if (rl == indb)
      return vstr(1,"b");
    
    if (matches[rl].size() > 0)
      return matches[rl];

    
    vstr ret;
    trav(el,rules[rl]) {
      vstr tret = go_dp(el[0]);
      //cout << tret.size() << endl;
      for(int i = 1; i < el.size(); ++i) {
        vstr tret2 = go_dp(el[i]);
        //cout << tret2.size() << endl;
        tret = merger(tret, tret2);
      }
      //cout << tret.size() << endl;
      ret.insert(ret.end(), tret.begin(), tret.end());
    }
    //cout << rl << " " << ret.size() << endl;
    return matches[rl] = ret;
  };

  vstr reachable = go_dp(0);
  set<string> reach_set = set<string>(all(reachable));

  int ret = 0;
  trav(el,msg)
    if (reach_set.count(el))
      ret++;

  cout << "Part 1 answer: " << ret << endl;

  // cout << 42 << " " << go_dp(42).size() << endl;
  // trav(el,go_dp(42))
  //   cout << el << endl;

  // cout << 31 << " " << go_dp(31).size() << endl;
  // trav(el,go_dp(31))
  //   cout << el << endl;

  vstr reach1 = go_dp(42), reach2 = go_dp(31);
  set<string> set1 = set<string>(all(reach1));
  set<string> set2 = set<string>(all(reach2));

  int l1 = (*set1.begin()).size();
  int l2 = (*set2.begin()).size();

  //cout << "Sizes: " << l1 << " " << l2 << endl;

  ret = 0;
  trav(ms,msg) {
    bool fl = false;
    int sz = ms.size();
    //if (sz != 2*l1 + l2)
    //  continue;
    for(int n1 = 2; n1 < sz / l1; n1++) {
      int szrem = sz - n1 * l1;
      if (szrem % l2)
        continue;
      int n2 = szrem / l2;
      if (n2 >= n1)
        continue;

      bool tfl = true;
      rep(i,n1)
        tfl &= set1.count(ms.substr(i*l1,l1));
      rep(i,n2)
        tfl &= set2.count(ms.substr(n1*l1 + i*l2, l2));
      
      if (tfl) {
        fl = true;
        break;
      }
    }
    if (fl) {
      //cout << ms << endl;
      ret++;
    }
  }

  cout << "Part 2 answer: " << ret << endl;

  return 0;
}

