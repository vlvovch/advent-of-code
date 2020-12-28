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

  queue<int> deck1, deck2;

  string tmp;
  int mode = -1;
  while (cin >> tmp) {
    if (tmp == "Player") {
      mode++;
      cin >> tmp;
      continue;
    }
    if (mode == 0) {
      deck1.push(atoi(tmp.c_str()));
    } else {
      deck2.push(atoi(tmp.c_str()));
    }
  }

  using decks = pair<queue<int>,queue<int>>;
  int rounds = 0;

  std::function<decks(decks)> playGame = [&](decks conf) {
    set<decks> played;
    while(!conf.first.empty() && !conf.second.empty()) {
      if (played.count(conf)) {
        // player 1 wins
        conf.second = queue<int>();
        return conf;
      }
      played.insert(conf);
      queue<int> &deck1 = conf.first;
      queue<int> &deck2 = conf.second;
      int c1 = deck1.front(); deck1.pop();
      int c2 = deck2.front(); deck2.pop();
      rounds++;

      if (deck1.size() >= c1 && deck2.size() >= c2) {
        // play a sub-game
        queue<int> opdeck1 = deck1, opdeck2 = deck2;
        queue<int> ndeck1, ndeck2;
        rep(i,c1) {
          ndeck1.push(opdeck1.front()); opdeck1.pop();
        }
        rep(i,c2) {
          ndeck2.push(opdeck2.front()); opdeck2.pop();
        }
        decks subgame = playGame({ndeck1,ndeck2});
        if (subgame.second.empty()) {
          deck1.push(c1);
          deck1.push(c2);
        } else {
          deck2.push(c2);
          deck2.push(c1);
        }
      } else {
        // standard
        if (c1 > c2) {
          deck1.push(c1);
          deck1.push(c2);
        } else {
          deck2.push(c2);
          deck2.push(c1);
        }
      }
    }
    return conf;
  };

  decks result = playGame({deck1,deck2});
  deck1 = result.first;
  deck2 = result.second;

  if (deck1.empty())
    swap(deck1,deck2);
  
  ll res = 0;
  while (!deck1.empty()) {
    res += deck1.front() * deck1.size();
    deck1.pop();
  }

  cout << "Rounds: " << rounds << endl;
  cout << "Part 2 answer: " << res << endl;

  return 0;
}

