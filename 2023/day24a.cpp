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

  struct Hailstone {
    long long x,y,z;
    long long vx,vy,vz;
  };


  vector<Hailstone> hs;
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
      hs.push_back(h);
    }
  }

  long long xymin = 7, xymax = 27;
  xymin = 200000000000000ll;
  xymax = 400000000000000ll;

  int ret = 0;
  for(int ih1 = 0; ih1 < hs.size(); ++ih1) {
    for(int ih2 = ih1 + 1; ih2 < hs.size(); ++ih2) {
      auto& hs1 = hs[ih1];
      auto& hs2 = hs[ih2];
      long long x0 = hs1.x, y0 = hs1.y, z0 = hs1.z;
      long long vx0 = hs1.vx, vy0 = hs1.vy, vz0 = hs1.vz;
      long long x1 = hs2.x, y1 = hs2.y, z1 = hs2.z;
      long long vx1 = hs2.vx, vy1 = hs2.vy, vz1 = hs2.vz;
      long long det = vx1*vy0 - vx0*vy1;
      if (det == 0) continue;
      long long t0p = (vy1*(x0 - x1) + vx1*(y1 - y0));
      long long t1p = (vy0*(x0 - x1) + vx0*(y1 - y0));
      double tx = x0 + vx0 * (double)t0p / det;
      double ty = y0 + vy0 * (double)t0p / det;
      cout.precision(16);
      //cout << tx << " " << ty << " " << t0p << " " << t1p << " " << det << endl;

      if (t0p > 0 && det < 0)
        continue;
      if (t0p < 0 && det > 0)
        continue;
      if (t1p > 0 && det < 0)
        continue;
      if (t1p < 0 && det > 0)
        continue;

      if (abs(tx - xymin) < 1.e9 || abs(tx - xymax) < 1.e9 || abs(ty - xymin) < 1.e9 || abs(ty - xymax) < 1.e9)
        cout << tx << " " << ty << endl;

      if (tx >= xymin && tx <= xymax && ty >= xymin && ty <= xymax) {
        ret++;
      }
    }
  }

  cout << ret << endl;

  return 0;
}

