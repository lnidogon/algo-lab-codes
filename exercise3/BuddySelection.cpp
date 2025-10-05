#include<iostream>
#include<vector>
#include<utility>
#include<string>
#include<set>
#include<algorithm>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;



int dist(std::vector<std::string> &atts1, std::vector<std::string> &atts2) {
  int x = 0, y = 0, ret = 0;
  while(x < (int)atts1.size() and y < (int)atts2.size()) {
    if(atts1[x] < atts2[y]) x++;
    else if(atts1[x] > atts2[y]) y++;
    else ret++, x++, y++;
  }
  return ret;
}

void solve() {
  int n, c, f;
  std::cin >> n >> c >> f;
  std::vector<std::string> temp2;
  std::vector<std::vector<std::string> > atts(n, temp2);
  std::vector<int> temp(n, -1);
  std::vector<std::vector<int> > w(n, temp);
  for(int i = 0; i < n; i++) {
      for(int j = 0; j < c; j++) {
      std::string a;
      std::cin >> a;
      atts[i].push_back(a);
    }
    std::sort(atts[i].begin(), atts[i].end());
  }
  for(int i = 0; i < n; i++) 
    for(int j = i + 1; j < n; j++) 
      w[i][j] = dist(atts[i], atts[j]);
  
  int lo = 0, mid, hi = c;
  while(lo < hi) {
    mid = (lo + hi + 1)/2;
    graph g(n);
    std::vector<boost::graph_traits< graph >::vertex_descriptor > mate(n);
    for(int i = 0; i < n; i++) 
      for(int j = i + 1; j < n; j++) 
        if(w[i][j] >= mid) 
          boost::add_edge(i, j, g);
    boost::edmonds_maximum_cardinality_matching(g, &mate[0]);
    bool success = ((int)boost::matching_size(g, &mate[0]) == n/2);
    if(success) lo = mid;
    else hi = mid - 1;
  }
  std::cout << (lo > f ? "not optimal" : "optimal") << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  for(std::cin >> t;t--;solve());
}