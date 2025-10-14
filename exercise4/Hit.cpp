#include<iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
using namespace std;
typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;

void solve(int n) {
  long  r, s, t, u;
  cin >> r >> s >> t >> u;
  IK::Point_2 p(r,s), q(t,u);
  IK::Ray_2 l(p,q);
  bool poss = false;
  for(int i = 0; i < n; i++) {
    long a, b, c, d;
    cin >> a >> b >> c >> d;
    if(poss) continue;
    IK::Point_2 p1(a,b), p2(c,d);
    IK::Segment_2 s(p1, p2);
    poss += CGAL::do_intersect(l,s);
    
  } 
  cout << (poss ? "yes" : "no") << '\n';
  
}
int main() {
  ios_base::sync_with_stdio(false);
  while(true) {
    int n;
    cin >> n;
    if(!n) break; 
    solve(n);
  }
}