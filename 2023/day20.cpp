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
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  struct Module {
    string name;
    int type; // 0 - broadcaster, 1 - flip-flop, 2 - conjunction
    int state; // 0 - off, 1 - on

    // For conjunction modules only
    map<string,int> inputs;
    vector<int> input_memory;

    // Outputs
    vector<string> dirs;
  };

  vector<Module> modules;
  map<string,int> modules_map;

  map<char,int> module_types_map = {
    {'%', 1},
    {'&', 2}
  };

  // Read the input
  {
    char cc[1000];
    // Read the rules
    while (cin.getline(cc, 1000)) {
      istringstream iss(cc);
      string mod, tmp, dir;
      iss >> mod >> tmp;

      assert(tmp == "->");
      Module module;
      if (mod[0] == '%') {
        module.type = 1;
        module.name = mod.substr(1);
      } else if (mod[0] == '&') {
        module.type = 2;
        module.name = mod.substr(1);
      } else {
        module.type = 0;
        module.name = mod;
      }

      module.state = 0;

      while(iss >> dir) {
        if (dir.back() == ',')
          dir.pop_back();
        module.dirs.push_back(dir);
      }

      modules_map[module.name] = modules.size();
      modules.push_back(module);
    }
  }

  

  // Fill conjunction inputs
  for(auto& module : modules) {
    for(auto& dir : module.dirs) {
      if (modules_map.count(dir) == 0)
        continue;
      auto& module_conj = modules[modules_map[dir]];
      if (module_conj.type != 2)
        continue;
      else {
        module_conj.inputs[module.name] = module_conj.input_memory.size();
        module_conj.input_memory.push_back(0);
      }
    }
  }

  // For Part 2
  string rx_in = "";
  vector<int> sq_in_days;
  map<string,int> sq_in_map;
  for(auto& module : modules) {
    for(auto& dir : module.dirs) {
      if (dir == "rx") {
        assert(rx_in == "");
        assert(module.type == 2);
        rx_in = module.name;
      }
    }
  }
  for(auto& module : modules) {
    for(auto& dir : module.dirs) {
      if (dir == rx_in) {
        assert(module.type == 2);
        sq_in_map[module.name] = sq_in_days.size();
        sq_in_days.push_back(0);
      }
    }
  }

  long long nevt = 0;
  long long total_low = 0, total_high = 0;

  bool rx_found = false;

  auto add_pulse = [&](int pulse_type, const string& to, const string& from = "") {
    if (pulse_type == 0)
      total_low++;
    else
      total_high++;
    if (to == rx_in && pulse_type == 1) {
      int tind = sq_in_map[from];
      if (sq_in_days[tind] == 0)
        sq_in_days[tind] = nevt + 1;
    }
  };

  auto check_if_done = [&]() {
    for(int days : sq_in_days)
      if (days == 0)
        return false;
    return true;
  };


  auto push_button = [&]() {
    queue<vector<int>> pulses; // Module direction, low (0) or high(1) pulse, from which module
    pulses.push({modules_map["broadcaster"], 0, 0});
    add_pulse(0, "broadcaster");
    while(!pulses.empty()) {
      auto pulse = pulses.front();
      pulses.pop();
      //cout << pulse[0] << " " << pulse[1] << " " << pulse[2] << endl;
      auto& module = modules[pulse[0]];
      if (module.type == 0) {
        // Broadcaster
        for(auto dir : module.dirs) {
          //cout << dir << endl;
          add_pulse(pulse[1], dir, module.name);  
          if (modules_map.count(dir) > 0)
            pulses.push({modules_map[dir], pulse[1], pulse[0]});
        }
      } else if (module.type == 1) {
        // Flip-flop
        if (pulse[1] == 0) {
          module.state = 1 - module.state;
          for(auto dir : module.dirs) {
            add_pulse(module.state, dir, module.name);
            if (modules_map.count(dir) > 0)
              pulses.push({modules_map[dir], module.state, pulse[0]});
          }
        }
      } else if (module.type == 2) {
        // Conjunction
        // Update the input memory
        assert(module.inputs.count(modules[pulse[2]].name) > 0);
        module.input_memory[module.inputs[modules[pulse[2]].name]] = pulse[1];

        // Count the number of high inputs
        int tsum = 0;
        for(int pulse_in : module.input_memory) {
          tsum += pulse_in;
        }
        
        if (tsum == module.input_memory.size()) {
          // All inputs are high
          module.state = 1;
        } else {
          // Some inputs are low
          module.state = 0;
        }
        for(auto dir : module.dirs) {
          add_pulse(1 - module.state, dir, module.name);
          if (modules_map.count(dir) > 0)
            pulses.push({modules_map[dir], 1 - module.state, pulse[0]});
        }
      }
    }
  };

  for(nevt = 0; nevt < 1000; ++nevt) {
    push_button();
  }

  cout << total_low << " " << total_high << " " << total_low * total_high << endl;
  cout << "Part 1 answer: " << total_low * total_high << endl;

  // Part 2
  // Simulate more days if needed
  for(nevt = 1000; !check_if_done(); ++nevt) {
    push_button();
  }

  cout << "Partial periods: ";
  for(int el : sq_in_days)
    cout << el << " ";
  cout << endl;

  // Compute LCM of all steps
  // Prime factorizaton
  auto primeFactorization = [](int n) {
    vector<pair<int,int>> ret;
    for(int i = 2; i * i <= n; ++i) {
      if (n % i == 0) {
        int tcnt = 0;
        while(n % i == 0) {
          n /= i;
          tcnt++;
        }
        ret.push_back(make_pair(i, tcnt));
      }
    }
    if (n > 1)
      ret.push_back(make_pair(n, 1));
    return ret;
  };

  // Compute LCM of all partial periods
  map<int,int> lcm_factorize;
  for(auto& s : sq_in_days) {
    auto factors = primeFactorization(s);
    for(auto& f : factors) {
      lcm_factorize[f.first] = max(lcm_factorize[f.first], f.second);
    }
  }
  
  long long ret = 1;
  for(auto& s : lcm_factorize) {
    for(int i = 0; i < s.second; ++i) {
      ret *= s.first;
    }
  }

  if (lcm_factorize.size() > 0)
    cout << "Part 2 answer: " << ret << endl;
  else
    cout << "Part 2 answer: " << "N/A" << endl;

  return 0;
}

