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
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  vector<long long> times, dists;
  char cc[1000];
  cin.getline(cc, 1000);
  string timestr = string(cc);
  cin.getline(cc, 1000);
  string diststr = string(cc);

  long long total_time = 0;

  {
    stringstream iss;
    iss << timestr;
    string tmp;
    iss >> tmp;
    assert(tmp == "Time:");
    string val;
    string tim;
    while (iss >> val) {
      tim += val;
    }
    total_time = stoll(tim);
  }

  long long record_distance;

  {
    stringstream iss;
    iss << diststr;
    string tmp;
    iss >> tmp;
    assert(tmp == "Distance:");
    string val;
    string dist;
    while (iss >> val) {
      dist += val;
    }
    record_distance = stoll(dist);
  }

  auto distfunc = [&](long long speed) {
    long long dist = speed * (total_time - speed);
    //cout << speed << " " << dist << endl;
    return dist;
  };

  auto binary_search_dir = [&](long long left, long long right, long long dist, int dir = 0) {
    while (right - left > 1) {
      //cout << left << " " << right << " " << distfunc(left) << " " << distfunc(right) << " " << dist << endl;
      long long mid = (left + right) / 2;
      if (dir == 0) {
        assert(distfunc(right) >= dist);
        assert(distfunc(left)  <= dist);
      } else {
        assert(distfunc(right) <= dist);
        assert(distfunc(left)  >= dist);
      }
     
      if (dir == 0) {
        if (distfunc(mid) > dist) {
          right = mid;
        } else {
          left = mid;
        }
      } else {
        if (distfunc(mid) <= dist) {
          right = mid;
        } else {
          left = mid;
        }
      }
    }

    if (dir == 0) {
      if (distfunc(left) > dist) {
        return left;
      } else {
        return right;
      }
    } else {
      if (distfunc(right) > dist) {
        return right;
      } else {
        return left;
      }
    }
    return left;
  };

  cout <<
   binary_search_dir(total_time / 2, total_time, record_distance, 1) -
    binary_search_dir(0, total_time / 2, record_distance, 0) + 1
   << endl;

  return 0;
}

