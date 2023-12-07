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

  vector<string> numbers = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
  };

  string line;
  int sum = 0;
  while (cin >> line) {
    cout << line << endl;
    int d1 = -1, d2 = -1;
    for(int ic = 0; ic < line.size(); ++ic) {
      char c = line[ic];
      if (c >= '1' && c <= '9') {
        if (d1 == -1)
          d1 = c - '0';
        d2 = c - '0';
      } else {
        for(int in = 0; in < numbers.size(); ++in) {
          string number = numbers[in];
          if (ic + 1 >= number.size() && line.substr(ic - number.size() + 1, number.size()) == number) {
            if (d1 == -1)
              d1 = in + 1;
            d2 = in + 1;
          }
        }
      }
    }
    sum += d1 * 10 + d2;
  }

  cout << sum << endl;

  return 0;
}

