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
typedef vector<vll> vvll;

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
#define yes cout<<"Yes"<<endl
#define YES cout<<"YES"<<endl
#define no cout<<"No"<<endl
#define NO cout<<"NO"<<endl
#define Decimal fixed<<setprecision(20)
#define INF 1000000000
#define LLINF 1000000000000000000LL

const int inf = 1e9;
const ll linf = 1LL << 50;
const double eps = 1e-10;
const int MOD = 1e9 + 7;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};



#define ZERO(a) memset(a,0,sizeof(a))
#define MINUS(a) memset(a,0xff,sizeof(a))
#define ITR(x,c) for(__typeof(c.begin()) x=c.begin();x!=c.end();x++)
template<class V> class MaxFlow_dinic {
  public:
    struct edge { int to,reve;V cap;};
    static const int MV = 1100;
    vector<edge> E[MV];
    int itr[MV],lev[MV];

    void add_edge(int x,int y,V cap) {
      E[x].push_back((edge){y,(int)E[y].size(),cap});
      E[y].push_back((edge){x,(int)E[x].size()-1,0}); // directed
      //E[y].push_back((edge){x,(int)E[x].size()-1,cap}); // undirect
    }

    void bfs(int cur) {
      MINUS(lev);
      queue<int> q;
      lev[cur]=0;
      q.push(cur);
      while(q.size()) {
        int v=q.front(); q.pop();
        ITR(e,E[v]) if(e->cap>0 && lev[e->to]<0) lev[e->to]=lev[v]+1, q.push(e->to);
      }
    }

    int dfs(int from,int to,V cf) {
      if(from==to) return cf;
      ITR(e,E[from]) if(e->cap>0 && lev[from]<lev[e->to]) {
        V f=dfs(e->to,to,min(cf,e->cap));
        if(f>0) {
          e->cap-=f;
          E[e->to][e->reve].cap += f;
          return f;
        }
      }
      return 0;
    }

    V maxflow(int from, int to) {
      V fl=0,tf;
      while(1) {
        bfs(from);
        if(lev[to]<0) return fl;
        ZERO(itr);
        while((tf=dfs(from,to,numeric_limits<V>::max()))>0) fl+=tf;
      }
    }
};


ll solve(vector<string> t){
  vvll s(3,vll(26,0));
  REP(i,3){
    REP(j,t.size())
      s[i][t[i][j]-'A']++;
  }

  ll n=t.size();
  MaxFlow_dinic<ll> mf;
  mf.add_edge(0,1,n/2);
  mf.add_edge(0,2,n/2);

  REP(i,26)
    mf.add_edge(1,3+i,s[0][i]);
  REP(i,26)
    mf.add_edge(2,3+i,s[1][i]);
  REP(i,26)
    mf.add_edge(3+i,29,s[2][i]);

  ll m=mf.maxflow(0,29);
  if(m==n)
    YES;
  else
    NO;

  return m;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vector<string> t(3);
  t[0]="AABCCD";
  t[1]="ABEDDA";
  t[2]="EDDAAA";

  assert(6==solve(t));

  t[0]="AAAAAB";
  t[1]="CCCCCB";
  t[2]="AAABCB";
  assert(5==solve(t));

}
