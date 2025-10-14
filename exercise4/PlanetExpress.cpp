#include<iostream>
#include<vector>
#include<utility>
#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/strong_components.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>

#define ll long long
using namespace boost;

ll ssc(std::vector< ll > &components, std::vector<std::vector<std::pair<ll, ll > > > &grap) {
    typedef graph_traits<adjacency_list< vecS, vecS, directedS > >::vertex_descriptor Vertex;
    adjacency_list< vecS, vecS, directedS > G;
    for(ll i = 0; i < (ll)grap.size(); i++) for(auto t : grap[i]) add_edge(i, t.first, G);
    std::vector< Vertex > root(num_vertices(G));
    std::vector< ll > component(num_vertices(G)),  discover_time(num_vertices(G));
    std::vector< default_color_type > color(num_vertices(G));
    ll num = strong_components(G,
        make_iterator_property_map(component.begin(), get(vertex_index, G)),
        root_map(make_iterator_property_map(root.begin(), get(vertex_index, G)))
            .color_map(
                make_iterator_property_map(color.begin(), get(vertex_index, G))));
    for(auto t : component) components.push_back(t);
    return num;
}

ll dijk(ll s, ll e, std::vector<std::vector<std::pair<ll, ll > > > &grap) {
    typedef adjacency_list< listS, vecS, directedS, no_property, property< edge_weight_t, ll > > graph_t;
    graph_t g(grap.size());
    for(ll i = 0; i < (ll)grap.size(); i++) for(auto t : grap[i]) add_edge(i, t.first, t.second, g);
    std::vector< ll > d(num_vertices(g));  
    dijkstra_shortest_paths(g, s, distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));
    return d[e];
}

void solve() {
  ll n, m, k, t;
  std::cin >> n >> m >> k >> t;
  std::vector<std::pair<ll, ll > > temp;
  std::vector<std::vector<std::pair<ll, ll > > > grap(n, temp);
  std::vector<bool> tn(n, 0);
  std::vector<ll> components;
  for(ll i = 0; i < t; i++) {
    ll x;
    std::cin >> x;
    tn[x] = 1;
  }
  for(ll i = 0; i < m; i++) {
    ll u, v, c;
    std::cin >> u >> v >> c;
    grap[u].push_back({v, c});
  }
  ll num = ssc(components, grap);
  std::vector<ll> temp2;
  std::vector<std::vector<ll> > linked(num, temp2);
  for(ll i = 0; i < n; i++) if(tn[i]) linked[components[i]].push_back(i);
  std::vector<std::vector<std::pair<ll, ll > > > new_grap(n + num + 1, temp);
  for(ll i = 0; i < n; i++) for(auto t : grap[i]) new_grap[i].push_back(t);
  for(ll i = 0; i < num; i++) if(linked[i].size() > 1) for(auto t : linked[i]) new_grap[i + n].push_back({t, 0}), new_grap[t].push_back({i + n, linked[i].size() - 1});
  for(ll i = 0; i < k; i++) new_grap[n + num].push_back({i, 0});
  ll ans = dijk(n + num, n - 1, new_grap);
  if(ans <= 1e6) std::cout << ans << '\n';
  else std::cout << "no\n";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  ll t;
  for(std::cin >> t; t--;solve());
}
