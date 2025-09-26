#include<bits/stdc++.h>
#define breturn return
#define ll long long 
using namespace std;
void solve(int t) {
  ll n, m, a, b, p, h, w;
  cin >> n >> m;
  cin >> a >> b;
  cin >> p >> h >> w;
  vector<pair<ll, ll> > va;
  vector<ll> vb(m);
  for(int i = 0; i < n; i++) {
    ll x, y;
    cin >> x >> y;
    va.push_back({x, y});
  }
  for(int i = 0; i < m; i ++) cin >> vb[i];
  vector<ll> temp(h + 1, -1);
  vector<vector<ll> > dp(n + 1, temp);
  dp[0][0] = 0;
  for(int i = 0; i < n; i++) {
    for(int j = n; j >= 1; j--) {
      for(int k = h; k >= max(h - va[i].second, 0LL); k--) 
        if(~dp[j - 1][k]) 
          dp[j][h] = max(dp[j][h], dp[j - 1][k] + va[i].first);
      for(int k = h; k >= va[i].second; k--)
        if(~dp[j - 1][k - va[i].second])
          dp[j][k] = max(dp[j][k], dp[j - 1][k - va[i].second] + va[i].first);
    }
  }

  int ans = 1e9;
  sort(vb.begin(), vb.end());
  reverse(vb.begin(), vb.end());
  for(int i = 0; i <= n; i++) {
    if(!~dp[i][h]) continue;
    ll cw = -a * i, cp = dp[i][h];
    for(int j = 0; j <= m; j++) {
      if(cp < p) break;
      if(cw >= w) {
        ans = min(ans, i + j);
        break;
      }
      if(j == m) continue;
      cw += vb[j];
      cp -= b;
    }
  }
  cout << (ans == 1e9?-1:ans) << '\n';
}
int main() {
  ios_base::sync_with_stdio(false);
  int t;
  for(cin >> t;t--;solve(t));
}