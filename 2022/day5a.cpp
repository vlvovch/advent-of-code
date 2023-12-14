#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif


#define _CRT_SECURE_NO_WARNINGS
#define LOCAL

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

  vector<string> input;

  {
    char cc[1000];
    string tmp;
    while (cin.getline(cc, 1000)) {
      tmp = string(cc);
      if (tmp == "")
        break;
      input.push_back(tmp);
    }
  }

  vector<vector<char>> crates;
  string numbers = input.back();
  for(int i = 1; i < numbers.size(); i += 4) {
    crates.push_back(vector<char>());
    for(int j = input.size() - 2; j >= 0; j--) {
      if (input[j][i] != ' ') {
        crates[i/4].push_back(input[j][i]);
      }
    }
  }

  // Make the moves
  {
    string smove, sto, sfrom;
    int move, from, to;
    while (cin >> smove >> move >> sfrom >> from >> sto >> to) {
      for(int im = 0; im < move; ++im) {
        crates[to-1].push_back(crates[from-1].back());
        crates[from-1].pop_back();
      }
    }
  }

  // Compute the answer
  string ret = "";
  for(int i = 0; i < crates.size(); ++i) {
    ret += crates[i].back();
  }

  cout << ret << endl;

  return 0;
}

