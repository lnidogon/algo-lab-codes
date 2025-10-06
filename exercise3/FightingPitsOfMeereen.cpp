#include<iostream>
#include<vector>
#include<set>

using namespace std;

const int inf = 1e9;

const int powmat[] = {
  1,
  2,
  4,
  8,
  16,
  32,
  64,
  128,
  256,
  512,
  1024,
  2048,
  4096
};

int rek(int p, int bm1, int bm2, int dif, int f, int m, vector<int> &x, vector<vector<vector<vector<vector<int> > > > > &dp) {
  if(p == (int)x.size()) return 0;
  if(~dp[f][dif][bm1][bm2][p]) return dp[f][dif][bm1][bm2][p];
  dp[f][dif][bm1][bm2][p] = -inf;
  set<int> uniq;
  int c1 = bm1%5;
  int c2 = (bm1/5)%5;
  if(c1 != 4 and m == 3) uniq.insert(c1);
  if(c2 != 4) uniq.insert(c2);
  uniq.insert(x[p]);
  int cbonus = 1000 * (int)uniq.size();
  uniq.clear();
  int ndif = dif;
  int nf = f;
  int nbm1 = bm1;
  if(f == 0) ndif = dif + 1;
  else {
    if(dif == 0) ndif = 1, nf = 0;
    else ndif = dif - 1;
  }
  nbm1 /= 5;
  nbm1 += x[p] * 5;
  if(cbonus - powmat[ndif] >= 0)
    dp[f][dif][bm1][bm2][p] = max(dp[f][dif][bm1][bm2][p], rek(p + 1, nbm1, bm2, ndif, nf, m, x, dp) + cbonus - powmat[ndif]);
  
  c1 = bm2%5;
  c2 = (bm2/5)%5;
  if(c1 != 4 and m == 3) uniq.insert(c1);
  if(c2 != 4) uniq.insert(c2);
  uniq.insert(x[p]);
  cbonus = 1000 * (int)uniq.size();
  ndif = dif;
  nf = f;
  int nbm2 = bm2;
  if(f == 1) ndif = dif + 1;
  else {
    if(dif == 0) ndif = 1, nf = 1;
    else ndif = dif - 1;
  }
  nbm2 /= 5;
  nbm2 += x[p] * 5;
  if(cbonus - powmat[ndif] >= 0)
    dp[f][dif][bm1][bm2][p] = max(dp[f][dif][bm1][bm2][p], rek(p + 1, bm1, nbm2, ndif, nf, m, x, dp) + cbonus - powmat[ndif]);
  
  return dp[f][dif][bm1][bm2][p];
  
}


void solve() {
  int n, k, m;
  cin >> n >> k >> m;
  vector<int> x(n, -1);
  for(int i = 0; i < n; i ++) cin >> x[i];
  vector<int> dp4(n, -1);
  vector<vector<int> > dp3(25, dp4);
  vector<vector<vector<int> > > dp2(25, dp3);
  vector<vector<vector<vector<int> > > > dp1(12, dp2);
  vector<vector<vector<vector<vector<int> > > > > dp(2, dp1);
  cout << rek(0, 24, 24, 0, 0, m, x, dp) << '\n';
}
int main() {
  ios_base::sync_with_stdio(false);
  int t;
  for(cin >> t; t--; solve());
}
