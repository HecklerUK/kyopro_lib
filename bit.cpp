
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


struct BIT{
  vll tree;
  ll n;

  BIT(ll n_):tree(n_+1,0),n(n_){
  }

  ll cumulativeSum(ll i){
    ll s=0;
    while(i>0){
      s += tree[i];
      i -= i&-i;
    }
    return s;
  }

  //[l, r)
  ll sum(ll l, ll r){
    ll res = cumulativeSum(r) - cumulativeSum(l);
    return res;
  }

  void add(ll i, ll x){
    i++;
    while(i<=n){
      tree[i] += x;
      i += i&-i;
    }
  }
};


//区間加算のBIT
template <typename T> struct BIT_AddSection {
  vector<T> dat[2];
  T UNITY_SUM = 0;                     // to be set

  /* [1, n] */
  BIT_AddSection(ll n) { init(n); }
  void init(ll n) { for (int iter = 0; iter < 2; ++iter) dat[iter].assign(n + 1, UNITY_SUM); }

  /* a, b are 1-indexed, [a, b) */
  inline void sub_add(ll p, ll a, T x) {
    for (ll i = a; i < (ll)dat[p].size(); i += i & -i)
      dat[p][i] = dat[p][i] + x;
  }
  inline void add(int a, int b, T x) {
    sub_add(0, a, x * -(a - 1));
    sub_add(1, a, x);
    sub_add(0, b, x * (b - 1));
    sub_add(1, b, x * (-1));
  }

  /* a is 1-indexed, [a, b) */
  inline T sub_sum(int p, int a) {
    T res = UNITY_SUM;
    for (int i = a; i > 0; i -= i & -i) res = res + dat[p][i];
    return res;
  }
  inline T sum(int a, int b) {
    return sub_sum(0, b - 1) + sub_sum(1, b - 1) * (b - 1)
      - sub_sum(0, a - 1) - sub_sum(1, a - 1) * (a - 1);
  }

  /* debug */
  void print() {
    for (int i = 1; i < (int)dat[0].size(); ++i)
      cout << sum(i, i + 1) << ",";
    cout << endl;
    }
};



int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  BIT bit(4);
  bit.add(0, 1);
  bit.add(1, 2);
  bit.add(2, 3);
  cout<<bit.sum(0,4)<<endl;
}



