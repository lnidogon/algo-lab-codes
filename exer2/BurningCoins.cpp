#include<bits/stdc++.h>
#define breturn return
using namespace std;

int rek(int x, int y, int p, vector<vector<int> > &dp, const vector<int> &v) {
  if(x > y) return 0;
  if(dp[x][y] == -1) {
    int ret1 = rek(x + 1, y, p + 1, dp, v);
    int ret2 = rek(x, y - 1, p + 1, dp, v); 
    if(p%2) dp[x][y] = min(ret1, ret2);
    else dp[x][y] = max(ret1 + v[x], ret2 + v[y]);
  }
  return dp[x][y];
  
}

void solve() {
  int n;
  cin >> n;
  vector<int> temp(n, -1);
  vector<vector<int> > dp(n, temp);
  vector<int> v(n);
  for(int i =0; i < n;i ++) cin >> v[i];
  cout << rek(0, n - 1, 0, dp, v) << '\n';
  
}
int main() {
  ios_base::sync_with_stdio(false);
  int t;
  for(cin >> t;t--;solve());
}