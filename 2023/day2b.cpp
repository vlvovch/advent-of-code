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

std::map<string,int> colormap = { {"red",0}, {"green",1}, {"blue",2} };

int main(int argc, char* argv[])
{
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  // Game string is in format:
  // Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
  auto read_games = [&](const string& game) {
    vector<string> parts = split(game, ':');
    int gameid = 0;
    {
      stringstream ss(parts[0]);
      string tmp;
      ss >> tmp >> gameid;
    }
    assert(parts.size() == 2);
    vector<string> reveals = split(parts[1], ';');
    vector<vector<int>> ret;
    for(auto& reveal : reveals) {
      vector<string> colors = split(reveal, ',');
      vector<int> counts = {0,0,0};
      for(auto& color: colors) {
        stringstream ss(color);
        int numb;
        string col;
        ss >> numb >> col;
        counts[colormap[col]] = numb;
      }
      ret.push_back(counts);
    }
    return make_pair(gameid, ret);
  };

  vector<int> color_limits = {12, 13, 14};

  int ret = 0;
  char cc[1000];
  while (cin.getline(cc,1000)) {
    string tmp = string(cc);
    if (tmp == "")
      continue;
    auto game = read_games(tmp);
    vector<int> minis = {0,0,0};
    for(auto& reveal: game.second) {
      for(int ic = 0; ic < 3; ++ic) {
        minis[ic] = max(minis[ic], reveal[ic]);
      }
    }
    int power = minis[0] * minis[1] * minis[2];
    ret += power;
  }

  cout << ret << endl;

  return 0;
}

