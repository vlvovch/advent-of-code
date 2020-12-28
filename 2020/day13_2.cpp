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

pair<ll,ll> extended_gcd(ll a, ll b) {
  ll old_r = a, r = b;
  ll old_s = 1, s = 0;
  ll old_t = 0, t = 1;

  while (r != 0) {
    ll quotient = old_r / r;
    ll tmp = old_r;
    old_r = r;
    r = tmp - quotient * r;
    tmp = old_s;
    old_s = s;
    s = tmp - quotient * s;
    tmp = old_t;
    old_t = t;
    t = tmp - quotient * t;
  }

  return {old_s, old_t};
}

ll modular_mult(ll a, ll b, ll mod) {
  ll res = 0;
  a = a % mod;
  while (b > 0) {
    if (b & 1)
      res = (res + a) % mod;
    
    a = (a * 2) % mod;
    b /= 2;
  }
  return res;
}

int main(int argc, char* argv[])
{
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
  //freopen("day13.txt", "r", stdin);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  int timestamp;
  cin >> timestamp;

  string tmp;
  cin >> tmp;
  vi buses;

  int ind = 0;
  string tmp2;
  while (ind < tmp.size()) {
    if (tmp[ind] != ',') {
      tmp2 += tmp[ind];
    } else {
      if (tmp2 != "x") {
        int tID = atoi(tmp2.c_str());
        buses.push_back(tID);
      }
      else {
        buses.push_back(-1);
      }
      tmp2 = "";
    }
    ind++;
  }
  if (tmp2 != "" && tmp2 != "x") {
    int tID = atoi(tmp2.c_str());
    buses.push_back(tID);
  }

  vector<ll> ns;
  vector<ll> as;
  rep(i,buses.size()) {
    if (buses[i] == -1)
      continue;
    
    ns.push_back(buses[i]);
    as.push_back((buses[i] - i%buses[i])%buses[i]);
  }

  ll ret = 0;
  ll cn = ns[0];
  ll ca = as[0];
  for(int ib = 1; ib < ns.size(); ++ib) {
    ll n1 = cn, n2 = ns[ib];
    ll ncn = n1 * n2;
    auto m1m2 = extended_gcd(n1, n2);
    
    while (m1m2.first < 0)
      m1m2.first += ncn;
    while (m1m2.second < 0)
      m1m2.second += ncn;

    m1m2.first %= ncn;
    m1m2.second %= ncn;

    ll a1 = ca, a2 = as[ib];
    ll a12 = modular_mult(modular_mult(a1, m1m2.second, ncn), n2, ncn);
    a12 += modular_mult(modular_mult(a2, m1m2.first, ncn), n1, ncn);

    a12 %= ncn;
    
    cn = n1 * n2;
    ca = a12;
    while (ca < 0)
       ca += cn;
    while (ca >= cn)
       ca -= cn;

    cout << "Check1: " << ca%n1 << " " << a1 << endl;
    cout << "Check2: " << ca%n2 << " " << a2 << endl;

  }

  cout << "Final check: " << cn << endl;
  rep(i,ns.size()) {
    cout << ca % ns[i] << " " << as[i] << endl;
  }

  cout << "Answer: ";
  cout << ca << endl;

  return 0;
}

