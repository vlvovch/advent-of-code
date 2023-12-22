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

  struct Block {
    int xmin, xmax;
    int ymin, ymax;
    int zmin, zmax;
  };

  vector<Block> blocks;

  int maxx = 0, maxy = 0, maxz = 0;
  // Read input
  {
    string s;
    while (cin >> s) {
      auto res = split(s, '~');
      assert(res.size() == 2);
      auto r1  = split(res[0], ',');
      assert(r1.size() == 3);
      auto r2  = split(res[1], ',');
      assert(r2.size() == 3);
      Block bl = {stoi(r1[0]), stoi(r2[0]), stoi(r1[1]), stoi(r2[1]), stoi(r1[2]), stoi(r2[2])};
      blocks.push_back(bl);
      maxx = max(maxx, stoi(r2[0]));
      maxy = max(maxy, stoi(r2[1]));
      maxz = max(maxz, stoi(r2[2]));
    } 
  }

  sort(blocks.begin(), blocks.end(), [](const Block& b1, const Block& b2) {
    return b1.zmin < b2.zmin;
  });

  vector<set<int>> blocks_over(blocks.size());
  vector<set<int>> blocks_under(blocks.size());

  // Filled space
  vector<vector<vector<int>>> space;
  space.resize(maxx+1);
  for(auto& el : space) {
    el.resize(maxy + 1);
    for(auto& el2 : el) {
      el2 = vector<int>(maxz + 1, -1);
    }
  }

  // Drop blocks one-by-one
  for(int ibl = 0; ibl < blocks.size(); ++ibl) {
    auto& block = blocks[ibl];
    while(block.zmin > 1) {
      set<int> sblocks_under;
      for(int x = block.xmin; x <= block.xmax; ++x) {
        for(int y = block.ymin; y <= block.ymax; ++y) {
          if (space[x][y][block.zmin - 1] != -1) {
            sblocks_under.insert(space[x][y][block.zmin - 1]);
          }
        }
      }
      if (sblocks_under.size() > 0) {
        for(auto el : sblocks_under) {
          blocks_over[el].insert(ibl);
          blocks_under[ibl].insert(el);
        }
        break;
      }
      block.zmin--;
      block.zmax--;
    }
    for(int x = block.xmin; x <= block.xmax; ++x) {
      for(int y = block.ymin; y <= block.ymax; ++y) {
        for(int z = block.zmin; z <= block.zmax; ++z) {
          space[x][y][z] = ibl;
        }
      }
    }
  }

  int ret = 0;
  for(int ibl = 0; ibl < blocks.size(); ++ibl) {
    bool can_disintegrate = true;
    for(auto el : blocks_over[ibl]) {
      if (blocks_under[el].size() == 1) {
        can_disintegrate = false;
        break;
      }
    }
    if (can_disintegrate)
      ret++;
  }

  cout << "Part 1 answer: " << ret << endl;

  // Part 2
  ret = 0;
  function<void(int)> disintegrate_block = [&](int ibl) {
    for(auto el : blocks_over[ibl]) {
      blocks_under[el].erase(ibl);
      if (blocks_under[el].size() == 0) {
        ret++;
        disintegrate_block(el);
      }
    }
    blocks_over[ibl].clear();
  };

  auto blocks_over_ini = blocks_over;
  auto blocks_under_ini = blocks_under;
  for(int ibl = 0; ibl < blocks.size(); ++ibl) {
    blocks_over = blocks_over_ini;
    blocks_under = blocks_under_ini;
    disintegrate_block(ibl);
  }

  cout << "Part 2 answer: " << ret << endl;

  return 0;
}

