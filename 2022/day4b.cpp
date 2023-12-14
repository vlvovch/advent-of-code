#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif


#define _CRT_SECURE_NO_WARNINGS
#define LOCAL

using namespace std;

// Split string using delimiter
std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

std::vector<std::string> split(const std::string& s, char delim) {
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
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

  int ret = 0;
  int ret2 = 0;

  string line;
  while (cin >> line) {
    auto elves = split(line, ',');
    auto elve1 = split(elves[0],'-');
    auto elve2 = split(elves[1],'-');
    int l1 = stoi(elve1[0]), r1 = stoi(elve1[1]);
    int l2 = stoi(elve2[0]), r2 = stoi(elve2[1]);
    if (l2 >= l1 && r2 <= r1)
      ret++;
    else if (l1 >= l2 && r1 <= r2)
      ret++;

    if (l2 >= l1 && l2 <= r1) {
      ret2++;
    }
    else if (r2 >= l1 && r2 <= r1)
      ret2++;
    else if (l1 >= l2 && l1 <= r2) {
      ret2++;
    }
    else if (r1 >= l2 && r1 <= r2)
      ret2++;
  }

  cout << "Part A: " << ret << endl;
  cout << "Part B: " << ret2 << endl;

  return 0;
}

