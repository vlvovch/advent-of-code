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
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  map<string,int> sizes;
  set<string> files; // Avoid double-counting
  vector<string> dirs = {"/"};

  // Process the commands
  char cc[1000];
  while (cin.getline(cc, 1000)) {
    string line(cc);
    if (line[0] == '$') {
      auto parts = split(line, ' ');
      if (parts[1] == "cd") {
        if (parts[2] == "..") {
          dirs.pop_back();
        } else if (parts[2] != "/") {
          dirs.push_back(dirs.back() + parts[2] + "/");
        }
      } else {
        assert(parts[1] == "ls");
      }
    } else {
      auto parts = split(line, ' ');
      auto size = parts[0];
      auto name = parts[1];
      if (size != "dir") {
        auto filename = dirs.back() + name;
        if (files.count(filename) > 0) {
          continue;
        } else {
          files.insert(filename);
          for (auto& dir : dirs) {
            sizes[dir] += stoi(size);
          }
        }
      }
    }
  }

  // Look for all dirs with size not more than 100000
  int ret = 0;
  for(auto& el : sizes) {
    cout << el.first << " " << el.second << endl;
    if (el.second <= 100000) {
      ret += el.second;
    }
  } 

  cout << "Part A: " << ret << endl;

  // Part B
  int free_space = 70000000 - sizes["/"];
  int need_to_free = 30000000 - free_space;

  if (need_to_free > 0) {
    vector<int> allsizes;
    for(auto& el: sizes) {
      allsizes.push_back(el.second);
    }
    sort(allsizes.begin(), allsizes.end());
    for(auto sz: allsizes) {
      if (sz >= need_to_free) {
        cout << "Part B: " << sz << endl;
        return 0;
      }
    }
  }

  return 0;
}

