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
  //freopen("day9.txt", "r", stdin);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  vector<ll> a(25);
  vector<ll> psums(25);
  rep(i,25) {
    cin >> a[i];
    psums[i] = a[i];
    if (i > 0)
      psums[i] += psums[i-1];
  }

  ll tmp;
  ll problem_number = -1;
  while (cin >> tmp) {
    int ist = a.size() - 25;
    bool fl = false;
    rep(i,24)
      rep(j,24) {
        if (a[ist+i] != a[ist + 1 + j] && a[ist + i] + a[ist + 1 + j] == tmp) {
          fl = true;
        }
      }

    if (!fl) {
      if (problem_number == -1) {
        problem_number = tmp;
        cout << "Part 1 answer: " << problem_number << endl;
      }
    }
    else {
      a.push_back(tmp);
      psums.push_back(tmp + psums.back());
    }
  }

  for(int i1 = 0; i1 < a.size() - 1; i1++) {
    for(int i2 = i1+1; i2 < a.size(); i2++) {
      ll ncand = psums[i2];
      if (i1 > 0)
        ncand -= psums[i1-1];
      
      if (ncand == problem_number) {
        cout << "Part 2 answer: " << 
          *std::min_element(a.begin() + i1, a.begin() + i2 + 1) + 
          *std::max_element(a.begin() + i1, a.begin() + i2 + 1)  << endl;
        return 0;
      }
    }
  }

  assert(0);
  
  return 0;
}

