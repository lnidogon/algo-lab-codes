#include<iostream>
#include<vector>
#include<set>
#include<utility>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<
boost::vecS,
boost::vecS,
boost::undirectedS,
boost::no_property,
boost::property<boost::edge_weight_t, int> 
>graph;

void solve() {
    int n, e, s, a, b;
    std::cin >> n >> e >> s >> a >> b;
    graph g(n);
    std::vector<graph> gsi(s);
    std::vector<int> h(s);
    for(int i = 0; i < e; i++) {
      int a, b;
      std::cin >> a >> b;
      for(int j = 0; j < s; j++) {
        int w;
        std::cin >> w;
        boost::add_edge(a, b, w, gsi[j]);
      }
    }
    for(int i = 0; i < s; i++) {
      int x;
      std::cin >> x;
      h[i] = x;
    }

    std::set<std::pair<int, std::pair<int, int> > > next_edge;
    
    for(int j = 0; j < s; j++) {
      next_edge.insert({-1, {-1, h[j]}});
      std::vector<bool> visited(n, 0);
      while(next_edge.size()) {
        std::pair<int, std::pair<int, int> > current_edge = *(next_edge.begin());
        next_edge.erase(next_edge.begin());
        int current_vertex = current_edge.second.second;
        if(visited[current_vertex]) continue;

        if(~current_edge.second.first) boost::add_edge(current_edge.second.first, current_edge.second.second, current_edge.first, g);
        visited[current_vertex] = true;
        for(auto edge_it = boost::out_edges(current_vertex, gsi[j]).first; 
        edge_it != boost::out_edges(current_vertex, gsi[j]).second; ++edge_it) {
          next_edge.insert(
            {
              boost::get(boost::edge_weight, gsi[j], *edge_it), 
              {
                current_vertex, 
                boost::target(
                  *edge_it, 
                  gsi[j]
                )
              }
            }
          );
        }
      }
    }
    std::vector<int> dist(n);
    boost::dijkstra_shortest_paths(g, a, 
      boost::distance_map(
        boost::make_iterator_property_map(
          dist.begin(),
          boost::get(boost::vertex_index, g)
        )
      )
    );
    std::cout << dist[b] << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  for(std::cin >> t; t--; solve());
}