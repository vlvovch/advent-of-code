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

  long long totret = 0;

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

    // Copy the strings and configs 4 times
    string totline = cline;
    vector<int> totconfig = config_int;
    for(int i = 0; i < 4; ++i) {
      totline += '?' + cline;
      totconfig.insert(totconfig.end(), config_int.begin(), config_int.end());
    }

    // After copying
    cout << totline << " ";
    for(auto& c : totconfig) {
      cout << c << ",";
    }
    cout << endl;

    // Use dynamic programming
    // The state is the position in the line and the number of remaining blocks to place
    vector<vector<long long>> dp(totline.size(), vector<long long>(totconfig.size() + 1, -1ll));
    function<long long(int, int)> go = [&](int pos, int config_st) {
      // We've placed too many blocks already
      if (config_st > totconfig.size())
        return 0ll;

      // We're at the end of the line, check if we placed exactly the right number of blocks
      if (pos == totline.size()) {
        return (config_st == totconfig.size() ? 1ll : 0ll);
      }

      // Check if we've already computed this state
      if (dp[pos][config_st] != -1ll)
        return dp[pos][config_st];
  
      // Calculate the state
      long long ret = 0;

      // Cannot place the block here, just move on
      if (totline[pos] == '.') {
        ret += go(pos+1, config_st);
      }

      // Can place the block here
      if (totline[pos] == '#' || totline[pos] == '?') {

        // Have to place the block here but we're out of blocks
        if (config_st >= totconfig.size() && totline[pos] == '#')
          return dp[pos][config_st] = 0;

        // Try to place the block here
        int tpos = pos;
        while ((totline[tpos] == '#' || totline[tpos] == '?') && tpos < totline.size() && tpos - pos < totconfig[config_st]) {
          tpos++;
        }

        // If we placed the block here, move on
        // Have to put a space between here and the potential next block
        if (tpos - pos == totconfig[config_st]) {
          // Reached the end
          if (tpos == totline.size())
            ret += go(tpos, config_st + 1);
          // Jump over to the next possible starting position
          else if (totline[tpos] != '#')
            ret += go(tpos+1, config_st + 1);
        }
      }

      // Can skip this block
      if (totline[pos] == '?') {
        ret += go(pos + 1, config_st);
      }
      
      return dp[pos][config_st] = ret;
    };

    // Calculate
    long long tret = go(0, 0);
    cout << tret << " " << endl;

    // Add to the sum
    totret += tret;
  }

  // Output
  cout << totret << endl;

  return 0;
}

