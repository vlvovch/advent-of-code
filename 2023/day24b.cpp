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


struct Hailstone {
  long long x,y,z;
  long long vx,vy,vz;
};


// Solve intersection assuming x = x1 and vx = vx0
Hailstone SolveIntersection(const Hailstone& h1, const Hailstone& h2, const Hailstone& h3) {
  double x1 = h1.x, y1 = h1.y, z1 = h1.z;
  double vx1 = h1.vx, vy1 = h1.vy, vz1 = h1.vz;
  double x2 = h2.x, y2 = h2.y, z2 = h2.z;
  double vx2 = h2.vx, vy2 = h2.vy, vz2 = h2.vz;
  double x3 = h3.x, y3 = h3.y, z3 = h3.z;
  double vx3 = h3.vx, vy3 = h3.vy, vz3 = h3.vz;

  double x = x1;
  double vx = vx1;
  double y = -(((x1 - x3)*((vy2 - vy3)*(x1 - x2) + (-vx1 + vx2)*y2) + (vx1 - vx3)*(x1 - x2)*y3)/
     (vx3*(x1 - x2) + vx1*(x2 - x3) + vx2*(-x1 + x3)));
  double z = -(((x1 - x3)*((vz2 - vz3)*(x1 - x2) + (-vx1 + vx2)*z2) + (vx1 - vx3)*(x1 - x2)*z3)/
     (vx3*(x1 - x2) + vx1*(x2 - x3) + vx2*(-x1 + x3)));
  double vy = (vx3*vy2*(x1 - x2) + vx1*vy2*(-x1 + x2) + vx1*vy3*(x1 - x3) + vx2*vy3*(-x1 + x3) + 
     vx1*vx1*(y2 - y3) + vx2*vx3*(y2 - y3) - vx1*(vx2 + vx3)*(y2 - y3))/
   (vx3*(x1 - x2) + vx1*(x2 - x3) + vx2*(-x1 + x3));
  double vz = (vx3*vz2*(x1 - x2) + vx1*vz2*(-x1 + x2) + vx1*vz3*(x1 - x3) + vx2*vz3*(-x1 + x3) + 
     vx1*vx1*(z2 - z3) + vx2*vx3*(z2 - z3) - vx1*(vx2 + vx3)*(z2 - z3))/
   (vx3*(x1 - x2) + vx1*(x2 - x3) + vx2*(-x1 + x3));
  
  return {llround(x), llround(y), llround(z), llround(vx), llround(vy), llround(vz)};
}


int main(int argc, char* argv[])
{
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  vector<Hailstone> hss;
  // Read the input
  {
    char cc[1000];
    while(cin.getline(cc, 1000)) {
      auto res = split(cc, '@');
      assert(res.size() == 2);
      auto coord = split(res[0], ',');
      assert(coord.size() == 3);
      auto vel = split(res[1], ',');
      Hailstone h = {stoll(coord[0]), stoll(coord[1]), stoll(coord[2]), 
      stoll(vel[0]), stoll(vel[1]), stoll(vel[2])};
      hss.push_back(h);
    }
  }

  cout << hss.size() << endl;

  auto check_intersect = [&](const Hailstone& hs) {
    bool fl = true;
    for(auto& h : hss) {
      fl &= (h.x - hs.x) * (h.vy - hs.vy) == (h.y - hs.y) * (h.vx - hs.vx);
      fl &= (h.x - hs.x) * (h.vz - hs.vz) == (h.z - hs.z) * (h.vx - hs.vx);
      if (!fl) {
        return false;
      }
    }
    return true;
  };

  auto shuffle_hs = [](Hailstone& hs) {
    swap(hs.x, hs.y);
    swap(hs.y, hs.z);
    swap(hs.vx, hs.vy);
    swap(hs.vy, hs.vz);
  };
  
  for(int shuffle = 0; shuffle < 3; ++shuffle) {
    // Solve intersection assuming x = x1 and vx = vx0
    for(int i = 0; i < hss.size(); ++i) {
      for(int j = 0; j < hss.size(); ++j) {
        for(int k = j + 1; k < hss.size(); ++k) {
          if (j != i && k != i) {
            auto hs = SolveIntersection(hss[i], hss[j], hss[k]);
            if (check_intersect(hs)) {
              // Shuffle back the coordinates and velocities
              for(int i = 0; i < 3 - shuffle; ++i)
                shuffle_hs(hs);
              cout << hs.x << " " << hs.y << " " << hs.z << endl;
              cout << hs.vx << " " << hs.vy << " " << hs.vz << endl;
              cout << "Answer: " << hs.x + hs.y + hs.z << endl;
              return 0;
            }
          }
        }
      }
    }

    // Shuffle x,y,z
    for(auto& hs : hss) {
      shuffle_hs(hs);
    }
  }

  return 0;
}

