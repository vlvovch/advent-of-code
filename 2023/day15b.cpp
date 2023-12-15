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

// Compute HASH
int HASH(const string& str) {
  int ret = 0;
  for(char c : str) {
    ret += (int)(c);
    ret *= 17;
    ret %= 256;
  }
  return ret;
}

// List of labels in all the boxes
vector<vector<string>> boxes_label(256);
// List of focal lengths in all the boxes
vector<vector<int>> boxes_focal(256);

// Perform one operation
void perform_operation(const string& op) {
  int box = 0;
  if (op.back() == '-') {
    string label = op.substr(0, op.size() - 1);
    box = HASH(label);
    int ind = find(boxes_label[box].begin(), boxes_label[box].end(), label) - boxes_label[box].begin();
    // Remove if found
    if (ind < boxes_label[box].size()) {
      boxes_label[box].erase(boxes_label[box].begin() + ind);
      boxes_focal[box].erase(boxes_focal[box].begin() + ind);
    }
  } else {
    // Add or replace
    auto vals = split(op, '=');
    string label = vals[0];
    int focal = stoi(vals[1]);
    box = HASH(label);
    int ind = find(boxes_label[box].begin(), boxes_label[box].end(), label) - boxes_label[box].begin();
    if (ind < boxes_label[box].size()) {
      boxes_focal[box][ind] = focal;
    } else {
      boxes_label[box].push_back(label);
      boxes_focal[box].push_back(focal);
    }
  }
}

int main(int argc, char* argv[])
{
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  int ret = 0;

  string s;
  cin >> s;

  vector<string> inputs = split(s, ',');

  for(auto input : inputs) {
    perform_operation(input);
  }

  for(int ibox = 0; ibox < boxes_focal.size(); ++ibox) {
    for(int islot = 0; islot < boxes_label[ibox].size(); ++islot) {
      //cout << ibox << " " << boxes_label[ibox][islot] << " " << boxes_focal[ibox][islot] << endl;
      ret += (ibox + 1) * (islot + 1) * boxes_focal[ibox][islot];
    }
  }

  // Output
  cout << ret << endl;

  return 0;
}

