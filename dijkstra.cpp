#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef vector<ll> vll;
typedef vector<ld> vld;
typedef vector<pll> vpl;

#define ALL(a) a.begin(),a.end()
#define SZ(a) ((int)a.size())
#define FI first
#define SE second
#define REP(i,n) for(int i=0;i<((int)n);i++)
#define REP1(i,n) for(int i=1;i<((int)n);i++)
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define PB push_back
#define EB emplace_back
#define MP(a,b) make_pair(a,b)
#define SORT_UNIQUE(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#define GET_POS(c,x) (lower_bound(c.begin(),c.end(),x)-c.begin())
#define Decimal fixed<<setprecision(20)
#define INF 1000000000
#define LLINF 1000000000000000000LL

const int inf = 1e9;
const ll linf = 1LL << 50;
const double eps = 1e-10;
const int MOD = 1e9 + 7;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};


struct Dijkstra{
  struct edge{
    ll to;
    ll cost;

    edge(ll x, ll y):to(x), cost(y){
    }
  };

  ll n;
  vector<vector<edge>> graph;
  vll dist;
  Dijkstra(ll n):n(n), graph(n), dist(n,LLINF){
  }

  void addEdge(ll from, ll to, ll cost){
    graph[from].push_back(edge(to, cost));
  }

  void calc(ll start){
    priority_queue<pll> que;
    que.push(pll(0,start));

    while(!que.empty()){
      pll p=que.top();
      que.pop();

      ll d=p.FI;
      ll now=p.SE;

      if(dist[now]<d)
        continue;

      for(auto e:graph[now]){
        if(dist[e.to]>d+e.cost){
          dist[e.to]=d+e.cost;
          que.push(pll(dist[e.to], e.to));
        }
      }
    }
  }

  ll getDist(ll x){
    return dist[x];
  }
};


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n=5;
  Dijkstra di(n);
  di.addEdge(0,1,2);
  di.addEdge(0,2,3);
  di.addEdge(1,2,2);
  di.addEdge(1,3,4);
  di.addEdge(2,4,5);

  di.calc(0);
  cout<<di.getDist(1)<<endl;
  cout<<di.getDist(2)<<endl;
  cout<<di.getDist(3)<<endl;
}
