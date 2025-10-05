#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/biconnected_components.hpp>
namespace boost
{
struct edge_component_t
{
    enum
    {
        num = 555
    };
    typedef edge_property_tag kind;
} edge_component;
}
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property,
boost::property<boost::edge_component_t, std::size_t > >
graph;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_t;

void solve() {
  int n, m;  
  std::cin >> n >> m;
  if(n == 0 or m == 0) {
    std::cout << 0 << '\n';
    return;
  }
  graph g(n);
  for(int i = 0; i < m; i++) { 
    int a, b;
    std::cin >> a >> b;
    boost::add_edge(a, b, g);
  }
  boost::property_map<graph, boost::edge_component_t >::type component = boost::get(boost::edge_component, g);
  biconnected_components(g, component);
  std::map<int, std::vector<std::pair<int, int> > > bridges;
  std::vector<std::pair<int, int> > ans;
  boost::graph_traits< graph >::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = boost::edges(g); ei != ei_end; ++ei) {
    int color = component[*ei];
    int a = boost::source(*ei, g);
    int b = boost::target(*ei, g);
    if(a > b) std::swap(a, b);
    bridges[color].push_back({a, b});
  }
  for(auto t : bridges) {
    if(t.second.size() == 1) ans.push_back(t.second.back()); 
  }
  std::sort(ans.begin(), ans.end());
  std::cout << ans.size() << '\n';
  for(auto t : ans) {
    std::cout << t.first << " " << t.second << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  int t;
  for(std::cin >> t;t--;solve());
}