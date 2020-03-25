
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


struct RollingHash{

  ll base1=1007;
  ll base2=2009;
  ll mod1=1000000007;
  ll mod2=1000000009;
  vll hash1, hash2, power1, power2;


  RollingHash(string s){
    ll n=s.size();
    hash1.assign(n+1, 0);
    hash2.assign(n+1, 0);
    power1.assign(n+1, 1);
    power2.assign(n+1, 1);


    for(ll i=0; i<n; i++){
      hash1[i+1] = (hash1[i]*base1+s[i])%mod1;
      power1[i+1] = (base1*power1[i])%mod1;
      hash2[i+1] = (hash2[i]*base2+s[i])%mod2;
      power2[i+1] = (base2*power2[i])%mod2;
    }

  }

  pll get(ll l, ll r){
    ll h1 = hash1[r]-hash1[l]*power1[r-l]%mod1;
    h1 = (mod1+h1)%mod1;
    ll h2 = hash2[r]-hash2[l]*power2[r-l]%mod2;
    h2 = (mod2+h2)%mod2;

    return pll(h1, h2);
  }

  ll calcLCP(ll a, ll b){
    ll maxlen = min(hash1.size()-a, hash1.size()-b);
    ll ok=0;
    ll ng=maxlen+1;
    while(abs(ok-ng)>1){
      ll mid = (ok+ng)/2;
      if(get(a, a+mid) == get(b, b+mid))
        ok = mid;
      else
        ng = mid;
    }

    return ok;
  }
};




int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s = "hogehoge";
  RollingHash rh(s);

  pll p1 = rh.get(0,4);
  pll p2 = rh.get(4,8);
  cout<<p1.FI<<endl;
  cout<<p2.FI<<endl;

  cout<<rh.calcLCP(0,4)<<endl;
}




