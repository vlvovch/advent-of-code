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

  const ll MOD = 20201227;

  ll pkeycard, pkeydoor;
  cin >> pkeycard >> pkeydoor;

  int dloopsize = 0;
  ll val = 1;
  while (val != pkeycard) {
    val *= 7;
    val %= MOD;
    dloopsize++;
  }

  cout << "Door loop size: " << dloopsize << endl;

  ll encrkey = 1;
  rep(i,dloopsize) {
    encrkey *= pkeydoor;
    //cout << encrkey << endl;
    encrkey %= MOD;
    //cout << encrkey << endl;
  }

  cout << "Encryption key: " << encrkey << endl;


  return 0;
}

