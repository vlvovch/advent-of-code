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
  //freopen("day8.txt", "r", stdin);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  struct oper{
    string typ;
    int numb;
  };

  vector<oper> ops;
  {
    string tmp, tmp2;
    int num;
    while (cin >> tmp >> tmp2) {
      num = atoi(tmp2.substr(1).c_str());
      if (tmp2[0] == '-')
        num = -num;
      ops.push_back({tmp,num});
    }
  }

  for(int icand = 0; icand < ops.size(); ++icand) {
    oper oorig = ops[icand];

    if (ops[icand].typ == "jmp") {
      ops[icand].typ = "nop";
    } else if (ops[icand].typ == "nop") {
      ops[icand].typ = "jmp";
    } else {
      continue;
    }

    vi opcnt(ops.size(), 0);

    int ci = 0;
    int accum = 0;
    while (ci < ops.size()) {
      const oper &op = ops[ci];

      if (opcnt[ci]) {
        break;
      }

      opcnt[ci]++;

      if (op.typ == "acc") {
        accum += op.numb;
        ci++;
      }
      else if (op.typ == "nop") {
        ci++;
      }
      else {
        ci += op.numb;
      }
    }

    if (ci >= ops.size()) {
      cout << accum << endl;
      ops[icand] = oorig;
    }
    else {
      ops[icand] = oorig;
    }

  }

  return 0;
}

