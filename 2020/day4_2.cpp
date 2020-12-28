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

  int ret = 0;

  char cc[600];
  map<string, string> fields;
  while (cin.getline(cc, 600)) {
    string tmp = string(cc);
    if (tmp.size() == 0) {
      bool valid = true;
      valid &= (bool)fields.count("byr");
      valid &= (bool)fields.count("iyr");
      valid &= (bool)fields.count("eyr");
      valid &= (bool)fields.count("hgt");
      valid &= (bool)fields.count("hcl");
      valid &= (bool)fields.count("ecl");
      valid &= (bool)fields.count("pid");

      if (!valid) {
        fields.clear();
        continue;
      }

      string field;
      
      field = fields["byr"];
      if (field.size() == 4) {
        int year = 0;
        trav(c,field) {
          valid &= (c >= '0' && c <= '9');
          year = year * 10 + (c - '0');
        }

        valid &= (year >= 1920 && year <= 2002);
      }
      else valid = false;


      field = fields["iyr"];
      if (field.size() == 4) {
        int year = 0;
        trav(c,field) {
          valid &= (c >= '0' && c <= '9');
          year = year * 10 + (c - '0');
        }

        valid &= (year >= 2010 && year <= 2020);
      }
      else valid = false;



      field = fields["eyr"];
      if (field.size() == 4) {
        int year = 0;
        trav(c,field) {
          valid &= (c >= '0' && c <= '9');
          year = year * 10 + (c - '0');
        }

        valid &= (year >= 2020 && year <= 2030);
      }
      else valid = false;


      field = fields["hgt"];
      if (field.size() >= 4) {
        string typ = field.substr(field.size() - 2);
        if (typ == "cm" && field.size() == 5) {
          int height = 0;
          rep(i,3) {
            char c = field[i];
            valid &= (c >= '0' && c <= '9');
            height = height * 10 + (c - '0');
          }
          valid &= (height >= 150 && height <= 193);
        } else if (typ == "in" && field.size() == 4) {
          int height = 0;
          rep(i,2) {
            char c = field[i];
            valid &= (c >= '0' && c <= '9');
            height = height * 10 + (c - '0');
          }
          valid &= (height >= 59 && height <= 76);
        } else {
          valid = false;
        }
      }
      else valid = false;

      field = fields["hcl"];
      if (field.size() == 7 && field[0] == '#') {
        rep(i,6) {
          char c = field[i+1];
          valid &= (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
        }
      }
      else {
        valid = false;
      }



      field = fields["ecl"];
      {
        set<string> ecls = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        valid &= (bool)ecls.count(field);
        //cout << (bool)ecls.count(field) << " ";
      }


      field = fields["pid"];
      if (field.size() == 9) {
        rep(i,9) {
          char c = field[i];
          valid &= (c >= '0' && c <= '9');
        }
      }
      else {
        valid = false;
      }

      //cout << valid << " ";

      ret += valid;
      fields.clear();

    }
    else {
      stringstream ss(tmp);
      while (ss >> tmp) {
        string fld = "";
        int ind = 0;
        while (ind < tmp.size() && tmp[ind] != ':')
          ind++;
        
        if (ind < tmp.size())
          fields[tmp.substr(0,ind)] = tmp.substr(ind + 1);
      }
    }
  }

  cout << ret << endl;

  return 0;
}

