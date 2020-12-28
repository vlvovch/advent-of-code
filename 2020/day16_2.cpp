#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<pii> vpii;
typedef vector<string> vstr;
template <class T> int size(const T& x) { return x.size(); }
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) (x).rbegin(), (x).rend() 
// const int INF = 2147483647;
#define FOR(i,a,b) for (__typeof(a) i=(a); i<(b); ++i)
#define iter(it,c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)
#define rep(i,n) for(int i=0;i<n;i++)
#define trav(a,x) for (auto&& a: x)
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl

#ifndef ONLINE_JUDGE
#define _CRT_SECURE_NO_WARNINGS
#define LOCAL
#endif

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

  vpii ranges;
  vector<string> field_names;
  vector<vpii> field_ranges;

  vi your_ticket;
  vector<vi> nearby_tickets(0);

  
  auto check_valid = [&](int num, const vpii& rnges) {
    trav(rng,rnges) {
      if (num >= rng.first && num <= rng.second)
        return true;
    }
    return false;
  };

  char cc[1000];
  int mode = 0;
  ll ret1 = 0;
  while (cin.getline(cc,1000)) {
    string tmp = string(cc);

    if (tmp == "")
      continue;

    stringstream ss(tmp);


    ss >> tmp;

    if (mode == 0) {
      string tmp2;
      while (tmp.back() != ':') {
        ss >> tmp2;
        tmp += " " + tmp2;
      }
      if (tmp == "your ticket:") {
        mode = 1;
        continue;
      }

      //cout << tmp << endl;
      field_names.push_back(tmp.substr(0,tmp.size() - 1));
      field_ranges.push_back(vpii());
      assert(tmp.back() == ':');

      string rang;
      

      while(ss >> rang) {
        string tnum = "";
        int ind = -1;
        int n1 = 0, n2 = 0;
        while (++ind < rang.size()) {
          if (rang[ind] == '-') {
            n1 = atoi(tnum.c_str());
            tnum = "";
          } else {
            tnum += rang[ind];
          }
        }
        n2 = atoi(tnum.c_str());

        ranges.push_back({n1,n2});
        field_ranges.back().push_back({n1,n2});
        
        if (!(ss >> rang))
          break;
        else {
          assert(rang == "or");
        }
      }
    }

    auto extract_values = [&](const string& inp) {
      vi ns;
      int ind = 0;
      string tnum = "";
      while (ind < inp.size()) {
        if (inp[ind] == ',') {
          ns.push_back(atoi(tnum.c_str()));
          tnum = "";
        } else {
          if (inp[ind] < '0' || inp[ind] > '9')
            return vi();
          tnum += inp[ind];
        }
        ind++;
      }
      if (tnum != "")
          ns.push_back(atoi(tnum.c_str()));
      
      return ns;
    };

    // your ticket
    if (mode == 1) {
      your_ticket = extract_values(string(cc));
      mode = 2;
      cin.getline(cc,1000);
    }


    // nearby tickets
    if (mode == 2) {
      string inp = string(cc);
      vi ns = extract_values(inp);

      bool fl = true;
      trav(n,ns) {
        fl &= check_valid(n, ranges);
        if (!check_valid(n,ranges))
          ret1 += n;
      }

      if (fl && ns.size())
        nearby_tickets.push_back(ns);

    }

  }

  cout << "Part 1 answer: " << ret1 << endl;


  // cout << "Your ticket: ";
  // trav(el,your_ticket)
  //   cout << el << " ";
  // cout << endl;

  // trav(ticket,nearby_tickets) {
  //   trav(el,ticket)
  //     cout << el << " ";
  //   cout << endl;
  // }

  map<int,int> field_to_pos;
  //vi usedpos(field_names.size(), 0);
  vii cands(field_names.size());
  for(int i1 = 0; i1 < field_names.size(); ++i1) {
    for(int ipos = 0; ipos < field_names.size(); ++ipos) {
      int cntgood = 0;
      rep(itck,nearby_tickets.size()) {
        if (check_valid(nearby_tickets[itck][ipos], field_ranges[i1]))
          cntgood++;
      }

      //cout << i1 << " " << ipos << " " << cntgood << " " << nearby_tickets.size() << endl;

      if (cntgood == nearby_tickets.size()) {
        cands[i1].push_back(ipos);
      }
    }
  }

  rep(i,field_names.size()) {
    int poscand = -1;
    rep(j,cands.size()) {
      if (cands[j].size() == 1) {
        poscand = cands[j][0];
        field_to_pos[j] = cands[j][0];
        break;
      }
    }

    rep(j,cands.size()) {
      rep(k,cands[j].size())
        if (cands[j][k] == poscand)
          cands[j].erase(cands[j].begin() + k);
    }
  }


  //trav(el,field_to_pos)
  //  cout << field_names[el.first] << " " << el.second << endl;

  ll ret = 1;
  trav(el,field_to_pos) {
    if (field_names[el.first].substr(0,9) == "departure")
      ret *= your_ticket[el.second];
  }

   cout << "Part 2 answer: " << ret << endl;

  return 0;
}

