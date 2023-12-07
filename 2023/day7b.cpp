#ifdef __APPLE__
#include "../aux/stdc++.h"
#else
#include <bits/stdc++.h>
#endif


#define _CRT_SECURE_NO_WARNINGS
#define LOCAL

using namespace std;

vector<int> compute_card_counts(const string& s) {
  map<char,int> cards;
  int jokers = 0;
  for(int i = 0; i < s.size(); ++i) {
    if (s[i] != 'J')
      cards[s[i]]++;
    else
      jokers++;
  }
  vector<int> ret;
  for(auto& p : cards) {
    if (p.second!=0)
      ret.push_back(p.second);
  }
  sort(ret.begin(), ret.end());
  reverse(ret.begin(), ret.end());
  if (ret.size() == 0)
    ret.push_back(jokers);
  else
    ret[0] += jokers;
  return ret;
}

std::map<char,int> card_scores = {
  {'J', 1},
  {'2', 2},
  {'3', 3},
  {'4', 4},
  {'5', 5},
  {'6', 6},
  {'7', 7},
  {'8', 8},
  {'9', 9},
  {'T', 10},
  {'J', 11},
  {'Q', 12},
  {'K', 13},
  {'A', 14},
};

bool cmp_cards(const char& c1, const char& c2) {
  return (card_scores[c1] < card_scores[c2]);
}

int hand_type(const string& hand) {
  vector<int> card_counts = compute_card_counts(hand);
  // Five of a kind
  if (card_counts.size() == 1) {
    return 7;
  } 
  // Four of a kind
  else if (card_counts.size() == 2 && card_counts[0] == 4) {
    return 6;
  }
  // Full house
  else if (card_counts.size() == 2 && card_counts[0] == 3) {
    return 5;
  }
  // Three of a kind
  else if (card_counts[0] == 3) {
    return 4;
  }
  // Two pair
  else if (card_counts.size() == 3 && card_counts[0] == 2) {
    return 3;
  }
  // One pair
  else if (card_counts.size() == 4 && card_counts[0] == 2) {
    return 2;
  }
  // High card
  else {
    return 1;
  }

}

bool cmp_hands(const string& h1, const string& h2) {
  auto h1type = hand_type(h1);
  auto h2type = hand_type(h2);
  if (h1type != h2type) {
    //cout << h1 << " " << h1type << endl;
    return h1type < h2type;
  }
  else {
    // Second ordering
    for(int i = 0; i < h1.size(); ++i) {
      if (h1[i] != h2[i])
        return cmp_cards(h1[i], h2[i]);
    }
  }
  return false;
}


int main(int argc, char* argv[])
{
  ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#ifdef LOCAL
  if (argc > 1) 
    freopen(argv[1], "r", stdin);
  if (argc > 2) 
    freopen(argv[2], "w", stdout);
#endif

  vector<pair<string, int>> hands;
  string tmp;
  int bidtmp;
  while (cin >> tmp >> bidtmp) {
    hands.push_back(make_pair(tmp, bidtmp));
  }

  sort(hands.begin(), hands.end(), [](const pair<string,int>& p1, const pair<string,int>& p2) {
    return cmp_hands(p1.first, p2.first);
  });

  long long ret = 0;
  for(int ih = 0; ih < hands.size(); ++ih) {
    cout << hands[ih].first << " " << hands[ih].second << endl;
    ret += (ih + 1) * hands[ih].second;
  }

  cout << ret << endl;

  return 0;
}

