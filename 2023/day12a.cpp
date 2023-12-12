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

  auto get_config = [&](const string& line) {
    vector<int> ret;
    int tlen = 0;
    for(char c : line) {
      if (c == '#') {
        tlen++;
      }
      else {
        if (tlen > 0)
          ret.push_back(tlen);
        tlen = 0;
      }
    }
    if (tlen > 0)
      ret.push_back(tlen);
    return ret;
  };

  long long ret = 0;

  char cc[1000];
  string conf;
  while (cin.getline(cc, 1000)) {
    string s(cc);
    auto parts = split(s, ' ');
    string cline = parts[0];
    auto config_s = split(parts[1], ',');
    vector<int> config_int;
    for(auto& numb : config_s) {
      config_int.push_back(stoi(numb));
    }

    cout << cline << " " << parts[1] << endl;

    // Use simple brute force
    string cline2 = cline;
    std::function<void(const string&, string&, int)> go = [&](const string& line, string& line2, int pos) {
      if (pos == line2.size()) {
        if (get_config(line2) == config_int) {
          ret++;
        }
        return;
      }
      if (line[pos] != '?')
        go(line, line2, pos + 1);
      else {
        line2[pos] = '#';
        go(line, line2, pos + 1);
        line2[pos] = '.';
        go(line, line2, pos + 1);
      }
    };

    go(cline, cline2, 0);
  }

  // Output
  cout << ret << endl;

  return 0;
}

