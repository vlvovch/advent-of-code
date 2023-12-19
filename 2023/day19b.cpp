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

  struct Condition {
    int type; // 0 - None, 1 - less, 2 - more
    char c;   // category
    int cond_val; // conditional value
    string ret;   // Next rule or result
  };

  typedef vector<Condition> Rule;

  vector<Rule> rules;
  map<string,int> rules_map;
  vector<vector<int>> parts;
  vector<vector<long long>> all_limits = {
    {0, 4000},
    {0, 4000},
    {0, 4000},
    {0, 4000}
  };
  map<char,int> categories_map = {
    {'x', 0},
    {'m', 1},
    {'a', 2},
    {'s', 3}
  };
  // Read the input
  {
    char cc[1000];
    // Read the rules
    while (cin.getline(cc, 1000)) {
      string s = string(cc);
      if (s == "")
        break;
      //cout << s << endl;
      auto vals = split(s, '{');
      auto rule_name = vals[0];
      auto conds = split(vals[1].substr(0,vals[1].size()-1), ',');

      auto ConditionFromString = [](const string& condition) {
        Condition ret;
        auto condi = split(condition, ':');
        if (condi.size() == 1) {
          ret.type = 0;
          ret.ret = condition;
        } else {
          assert(condi.size() == 2);
          if (condi[0][1] == '<')
            ret.type = 1;
          else
            ret.type = 2;
          ret.c = condi[0][0];
          //cout << condi[0] << " " << condi[1] << " " << split(condi[0],condi[0][1]).back() << endl;
          ret.cond_val = stoi(split(condi[0],condi[0][1]).back());
          ret.ret = condi[1];

        }
        //cout << ret.type << " " << ret.ret << endl;
        return ret;
      };

      Rule new_rule;
      for(auto& condstr : conds) {
        auto cond = ConditionFromString(condstr);
        new_rule.push_back(cond);

        if (cond.type == 1) {
          all_limits[categories_map[cond.c]].push_back(cond.cond_val - 1);
        } else if (cond.type == 2) {
          all_limits[categories_map[cond.c]].push_back(cond.cond_val);
        }
      }
      rules.push_back(new_rule);
      rules_map[rule_name] = rules.size() - 1;
    }

    // Read the parts
    while (cin.getline(cc, 1000)) {
      string s = string(cc);
      auto partsin = split(s.substr(1,s.size()-2),',');
      assert(partsin.size() == 4);
      vector<int> part;
      for(int i = 0; i < 4; ++i) {
        assert(categories_map[partsin[i][0]] == i);
        part.push_back(stoi(partsin[i].substr(2,partsin[i].size()-2)));
        //cout << part.back() << " ";
      }
      //cout << endl;
      parts.push_back(part);
    }
  }

  // Process the part across the whole worklow until return R or A
  function<string(const vector<int>&)> process_part = [&](const vector<int>& part) {
    string workflow = "in";
    while (workflow != "R" && workflow != "A") {
      Rule rule = rules[rules_map[workflow]];
      for(int icond = 0; icond < rule.size(); ++icond) {
        if (rule[icond].type == 0
          || (rule[icond].type == 1 && part[categories_map[rule[icond].c]] < rule[icond].cond_val)
          || (rule[icond].type == 2 && part[categories_map[rule[icond].c]] > rule[icond].cond_val)
        ) {
          workflow = rule[icond].ret;
          break;
        }
      }
    }
    return workflow;
  };
  
  int ret = 0;
  for(auto& part: parts) {
    if (process_part(part) == "A") {
      for(int i = 0; i < 4; ++i) 
        ret += part[i];
    }
  }
  // Output
  cout << "Part I: " << ret << endl;


  // Now do the part II
  long long bigret = 0;

  


  auto add_ret_range = [&](const vector<int>& low, const vector<int>& high) {
    long long tret = 1;
    for(int i = 0; i < low.size(); ++i) {
      assert(low[i] <= high[i]);
      tret *= (long long)(high[i]) - (long long)(low[i]) + 1;
    }
    bigret += tret;
  };

  function<void(const string&,vector<int>&, vector<int>&)> dfs 
  = [&](const string& node,vector<int>& low, vector<int>& high) 
  {
    if (node == "A") {
      add_ret_range(low, high);
      return;
    }
    if (node == "R") {
      return;
    }

    Rule rule = rules[rules_map[node]];
    for(auto& cond : rule) {
      //cout << cond.ret << endl;
      if (cond.type == 0) {
        dfs(cond.ret, low, high);
      } else {
        if (cond.type == 1) {
          // Less
          int icat = categories_map[cond.c];
          int new_max = cond.cond_val - 1;
          if (new_max >= low[icat]) {
            vector<int> new_low = low, new_high = high;
            new_high[icat] = min(high[icat], new_max);
            dfs(cond.ret, new_low, new_high);
          }
          int new_min = cond.cond_val;
          if (new_min <= high[icat]) {
            low[icat] = max(low[icat], new_min);
          } else {
            break;
          }
        } else {
          // Greater
          assert(cond.type == 2);
          int icat = categories_map[cond.c];
          int new_min = cond.cond_val + 1;
          if (new_min <= high[icat]) {
            vector<int> new_low = low, new_high = high;
            new_low[icat] = max(low[icat], new_min);
            dfs(cond.ret, new_low, new_high);
          }
          int new_max = cond.cond_val;
          if (new_max >= low[icat]) {
            high[icat] = min(high[icat], new_max);
          } else {
            break;
          }
        }
      }
    }
  };

  vector<int> curmin = {1,1,1,1};
  vector<int> curmax = {4000, 4000, 4000, 4000};
  dfs("in", curmin, curmax);

  cout << "Part II: " << bigret << endl;

  return 0;
}

