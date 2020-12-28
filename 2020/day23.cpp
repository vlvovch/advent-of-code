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

  string scups;
  cin >> scups;

  int nmax = scups.size();
  struct cup {
    int val;
    cup *prev;
    cup *next;
  };

  vector<cup> cups(nmax);
  rep(i,nmax) {
    cups[i] = {scups[i] - '1', NULL, NULL};
  }
  rep(i,nmax) {
    int inext = (i + 1) % nmax;
    int iprev = i -1;
    if (iprev < 0)
      iprev += nmax;
    cups[i].prev = &cups[iprev];
    cups[i].next = &cups[inext];
  }

  cup *current_cup = &cups[0];
  int moves = 100;
  while (moves--) {
    cup *cup1 = current_cup->next;
    cup *cup2 = cup1->next;
    cup *cup3 = cup2->next;
    current_cup->next = cup3->next;
    current_cup->next->prev = current_cup;

    cup1->prev = NULL;
    cup3->next = NULL;

    int ndest = (current_cup->val - 1 + nmax)%nmax;
    while (cup1->val == ndest || cup2->val == ndest || cup3->val == ndest) {
      ndest = (ndest - 1 + nmax)%nmax;
    }
    cup *destination_cup;
    trav(el,cups)
      if (el.val == ndest)
        destination_cup = &el;
    
    cup3->next = destination_cup->next;
    cup3->next->prev = cup3;
    destination_cup->next = cup1;
    cup1->prev = destination_cup;

    current_cup = current_cup->next;
  }

  cup *start_cup;
  trav(el,cups)
    if (el.val == 0)
      start_cup = &el;

  start_cup = start_cup->next;

  string ret = "";
  while(1) {
    if (start_cup->val == 0)
      break;
    ret += start_cup->val + '1';
    start_cup = start_cup->next;
  }

  cout << ret << endl;

  return 0;
}

