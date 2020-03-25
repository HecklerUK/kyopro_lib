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


struct Sieve{
  ll n;
  vll table;
  Sieve(ll n):n(n), table(n+1,0){
    for(ll i = 2; i<=n; i++){
      if(table[i])
        continue;

      table[i] = i;
      for(ll j = i*i; j<=n; j+=i)
        table[j] = i;
    }
  }

  vll factorList(ll x){
    vll res;
    while(x>1){
      res.push_back(table[x]);
      x /= table[x];
    }

    return res;
  }


  vpl getFact(ll x){
    map<ll, ll> m;
    vll fa = factorList(x);
    for(auto p:fa)
      m[p] += 1;

    SORT_UNIQUE(fa);
    vpl res;
    for(auto p:fa)
      res.push_back(pll(p, m[p]));

    return res;
  }
};


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  Sieve s(1000005);
  vpl facts = s.getFact(100);

  for(auto f:facts)
    cout<<f.FI<<":"<<f.SE<<endl;
}



