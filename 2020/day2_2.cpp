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

  string policy, letter, password;

  int numvalid = 0;
  while (cin >> policy >> letter >> password) {
    int low = 0, high = 0;
    int ind = 0;
    while (policy[ind] != '-') {
      low = 10 * low + (policy[ind] - '0');
      ind++;
    }
    ind++;
    while (ind < policy.size()) {
      high = 10 * high + (policy[ind] - '0');
      ind++;
    }

    char lett = letter[0];

    int cntlett = 0;
    rep(i,password.size())
      if ((i + 1 == low || i + 1 == high) && password[i] == lett)
        cntlett++;

    numvalid += (cntlett == 1);
  }

  cout << numvalid << endl;

  return 0;
}

