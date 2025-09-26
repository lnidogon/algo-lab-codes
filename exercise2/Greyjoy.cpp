#include<bits/stdc++.h>
#define breturn return
using namespace std;

int two_pointer(int k, vector<int> &c, vector<int> &v) {
  int x = 0, y = -1;
  int res = 0, sum = 0;
  while(y < (int)v.size()) {
    if(sum > k) sum -= c[v[x++]];
    else {
      if(sum == k) res = max(res, y - x + 1);
      if(y == (int)v.size() - 1) break;
      sum += c[v[++y]];
    }
  }
  return res;
}


void solve(int t) {
  int n, k, w;
  cin >> n >> k >> w;
  vector<int> c(n);
  vector<pair<int, pair<int, int> > > hlp(k + 1, {-1, {-1, -1}});
  for(int i = 0; i < n; i++) cin >> c[i];
  vector<int> temp;
  vector<vector<int> > wv;
  for(int i = 0; i < w; i++) {
    int l, x;
    cin >> l;
    for(int j = 0; j < l; j++) {
      cin >> x;
      temp.push_back(x);
    }
    wv.push_back(temp);
    temp.clear();
  }
  int ans = 0;
  if(ans == c[0]) ans = 1;
  for(auto v:wv) ans = max(ans, two_pointer(k, c, v));
  for(int i = 0; i < w; i++) {
    int ps = 0;
    for(int j = 1; j < (int)wv[i].size(); j++) {
      auto t = wv[i][j];
      ps += c[t];
      if(ps > k) break;
      if(hlp[ps].second.first < j) {
        hlp[ps].first = i;
        hlp[ps].second.second = hlp[ps].second.first;
        hlp[ps].second.first = j;
      } else if(hlp[ps].second.second < j) hlp[ps].second.second = j;
    }
  }
  for(int i = 0; i < w; i++) {
    long long ps = c[0];
    for(int j = 1; j < (int)wv[i].size(); j++) {
      ps += c[wv[i][j]];
      if(ps > k) break;
      int fnd = k - ps;
      int cans = j + 1;
      pair<int, pair<int, int>> fres = hlp[fnd];
      if(fres.first == -1) continue;
      if(fres.first == i) {
        if(fres.second.second == -1) continue; 
        cans += fres.second.second;
      }
      else cans += fres.second.first;
      
      ans = max(ans, cans);

    }
  }
  cout << ans << '\n';
  
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  for(cin >> t; t--;) solve(t);
}