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

ll compute(const string& expr) {
  vector<ll> nums;
  vector<char> ops;

  int braces = 0;
  int ind = -1;
  string trec = "";
  while (++ind < expr.size()) {

    if (braces == 0) {
      if (expr[ind] == ' ')
        continue;
      
      if (expr[ind] >= '0' && expr[ind] <= '9') {
        nums.push_back(expr[ind] - '0');
        continue;
      }

      if (expr[ind] == '*' || expr[ind] == '+') {
        ops.push_back(expr[ind]);
        continue;
      }

      if (expr[ind] == '(') {
        braces++;
      }
    } else {
      if (expr[ind] == ')') {
        braces--;
        if (braces > 0) {
          trec += expr[ind];
        } else {
          nums.push_back(compute(trec));
          trec = "";
        }
      } else {
        if (expr[ind] == '(')
          braces++;
        trec += expr[ind];
      }
    }
  }

  assert(nums.size() == (ops.size() + 1));

  rep(i,ops.size()) {
    if (ops[i] == '+') {
      ll tsum = nums[i] + nums[i+1];
      nums[i] = nums[i+1] = tsum;
      int j = i - 1;
      while (j >= 0 && ops[j] == '+') {
        nums[j] = nums[j + 1];
        j--;
      }
    }
  }

  //trav(el,nums)
  //  cout << el << " ";
  //cout << endl;

  ll ret = nums[0];
  rep(i,ops.size()) {
    if (ops[i] == '*')
      ret *= nums[i+1];
  }

  return ret;
}

int main(int argc, char* argv[])
{
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
  //freopen("day18.txt", "r", stdin);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  char cc[1000];
  ll ret = 0;
  while (cin.getline(cc,1000)) {
    ret += compute(string(cc));
  }

  cout << ret << endl;


  return 0;
}

