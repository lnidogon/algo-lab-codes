#include<iostream>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<
boost::vecS,
boost::vecS,
boost::undirectedS,
boost::no_property,
boost::property<boost::edge_weight_t, int> 
> weighted_graph;

typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;

typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type WeightMap;

int dijkstra_dist(const weighted_graph &G) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(G, 0, 
    boost::distance_map(
      boost::make_iterator_property_map(
        dist_map.begin(),
        boost::get(boost::vertex_index, G)
      )
    )
  );
  int ret = 0;
  for(int i = 0; i < n; i++) ret = std::max(ret, dist_map[i]);
  return ret;
}

int kruskal(weighted_graph &G) {
  std::vector<edge_desc> mst;
  
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
  WeightMap weight_map = boost::get(boost::edge_weight, G);

  int sum = 0;
  for(std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
    sum += weight_map[*it];
  }
  return sum;
}

void solve() {
  int n, m;
  std::cin >> n >> m;
  weighted_graph G(n);
  for(int i = 0; i < m; i++) {
    int a, b, c;
    std::cin >> a >> b >> c;
    boost::add_edge(a, b, c, G);
  }
  std::cout << kruskal(G) << " " << dijkstra_dist(G) << '\n';

  
}
int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  for(std::cin >> t; t--; solve());
}