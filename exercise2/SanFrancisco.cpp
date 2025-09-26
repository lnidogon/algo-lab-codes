///2
#include<bits/stdc++.h>
#define breturn return
#define ll long long
using namespace std;

// this code was written on phone

ll rek(int x, int k, vector<vector<ll> > &dp, const vector<vector<pair<ll, ll> > > &grap) {
  if(k==0) return 0;
  if(!~dp[k][x]) {
    dp[k][x] = 0;
    if(grap[x].size()) {
      for(auto t:grap[x]) {
        dp[k][x] = max(
          dp[k][x],
          rek(t.first, k - 1, dp, grap) + t.second
        );
      }
    } else dp[k][x] = rek(0, k, dp, grap);
  }
  return dp[k][x];
}

void solve(int t) {
  long long  n, m, x, k;
  cin >> n >> m >> x >> k;
  vector<pair<ll, ll> > temp;
  vector<vector<pair<ll, ll> > > grap(n, temp);
  for(int i = 0; i < m; i++) {
    int u, v, p;
    cin >> u >> v >> p;
    grap[u].push_back({v,p});
  }
  vector<ll> temp2(n, -1);
  vector<vector<ll> > dp(k + 1, temp2);
  for(int i = 0; i <= k; i++) rek(0, i, dp, grap);
  for(int j = 1; j <= k; j++) {
    if(dp[j][0] >= x) {
      cout << j << '\n';
      return;
    }
  }
  cout << "Impossible\n";
}
int main() {
  ios_base::sync_with_stdio(false);
  int t;
  for(cin >> t;t--;solve(t));
}