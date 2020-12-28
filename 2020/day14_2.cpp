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

map<ll,ll> mem;

ll num_from_bitmask(const string& bitmask)
{
  ll ret = 0;
  trav(bit,bitmask) {
    ret *= 2;
    ret += (bit - '0');
  }
  return ret;
}

void gowrite(string& mask, ll value, int pos)
{
  if (pos >= mask.size()) {
    mem[num_from_bitmask(mask)] = value;
    return;
  }

  if (mask[pos] == 'X') {
    mask[pos] = '0';
    gowrite(mask, value, pos + 1);
    mask[pos] = '1';
    gowrite(mask, value, pos + 1);
    mask[pos] = 'X';
  } else gowrite(mask, value, pos + 1);
}

int main(int argc, char* argv[])
{
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  string mask;


  string tmp1, tmp2, tmp3;
  while (cin >> tmp1 >> tmp2 >> tmp3) {
    if (tmp1 == "mask") {
      mask = tmp3;
    }
    else {
      assert(tmp1.substr(0,3) == "mem");

      ll value = atoi(tmp3.c_str());

      ll pos = atoi(tmp1.substr(4, tmp1.size() - 5).c_str());
      string sval = "";

      rep(ibit,36) {
        sval += '0' + (pos%2);
        pos /= 2;
      }

      reverse(all(sval));

      rep(ibit,36) {
        if (mask[ibit] == 'X')
          sval[ibit] = 'X';
        else if (mask[ibit] == '1')
          sval[ibit] = '1';
      }

      gowrite(sval, value, 0);
    }
  }

  ll ret = 0;
  trav(el,mem)
    ret += el.second;

  cout << ret << endl;

  return 0;
}

