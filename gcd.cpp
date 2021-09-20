#include <bits/stdc++.h>

#define all(a) a.begin(),a.end()
#define sz(a) (int)(a).size()
#define fi first
#define se second
#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<(n);i++)
#define drep(i,n) for(int i=(n)-1;i>=0;i--)
#define srep(i,n,s) for(int i=(s);i<(n);i++)
#define dsrep(i,n,s) for(int i=(n)-1;i>=(s);i--)
#define pb push_back
#define eb emplace_back
#define mp(a,b) make_pair(a,b)
#define getp(c,x) (lower_bound(c.begin(),c.end(),x)-c.begin())
#define yes cout<<"Yes"<<endl
#define YES cout<<"YES"<<endl
#define no cout<<"No"<<endl
#define NO cout<<"NO"<<endl
#define Decimal fixed<<setprecision(20)

using namespace std;
template<typename T> using vc = vector<T>;
template<typename T> using vv = vc<vc<T>>;
template<typename T> using pc = pair<T, T>;
template<typename T> using pq = priority_queue<T, vc<T>, greater<T>>;
using ll = long long;
using ld = long double;
using T3 = tuple<ll,ll,ll>;
using vll = vc<ll>;
using vld = vc<ld>;
using pll = pc<ll>;
using pld = pc<ld>;
using vpl = vc<pll>;
using vs = vc<string>;
using vvll = vv<ll>;
using vt = vc<T3>;


template<typename T>istream& operator>>(istream&i,vc<T>&v){rep(j,sz(v))i>>v[j];return i;}
template<typename T>string join(const vc<T>&v,const string& d=""){stringstream s;rep(i,sz(v))(i?s<<d:s)<<v[i];return s.str();}
template<typename T>ostream& operator<<(ostream&o,const vc<T>&v){if(sz(v))o<<join(v," ");return o;}
template<typename T1,typename T2>istream& operator>>(istream&i,pair<T1,T2>&v){return i>>v.fi>>v.se;}
template<typename T1,typename T2>ostream& operator<<(ostream&o,const pair<T1,T2>&v){return o<<v.fi<<","<<v.se;}
template<typename T>bool mins(T& x,const T&y){if(x>y){x=y;return true;}else return false;}
template<typename T>bool maxs(T& x,const T&y){if(x<y){x=y;return true;}else return false;}
template<typename T>ll suma(const vc<T>&a){ll res(0);for(auto&&x:a)res+=x;return res;}
// template<typename T>void uni(vc<T>& a){sort(all(a));a.erase(unique(rng(a)),a.end());}
template<typename T>void uni(T& a){sort(all(a));a.erase(unique(rng(a)),a.end());}

const int INF = 1001001001;
const ll LINF = 1LL << 50;
const double eps = 1e-10;
const int MOD = 1e9 + 7;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};

ll mod(ll a, ll m) {
    return (a % m + m) % m;
}

// 拡張 Euclid の互除法
ll extGCD(ll a, ll b, ll &p, ll &q) {
    if (b == 0) { p = 1; q = 0; return a; }
    ll d = extGCD(b, a%b, q, p);
    q -= a/b * p;
    return d;
}

// 入力x ≡ b1(mod. m1)に対して
// 答えを x ≡ r (mod. M) として、{r, M} をリターン
// 存在しない場合は {0, -1} をリターン
pll ChineseRem(const vll &b, const vll &m) {
    ll r = 0, M = 1;
    for (int i = 0; i < (int)b.size(); ++i) {
        ll p, q;
        ll d = extGCD(M, m[i], p, q); // p is inv of M/d (mod. m[i]/d)
        if ((b[i] - r) % d != 0) return make_pair(0, -1);
        ll tmp = (b[i] - r) / d * p % (m[i]/d);
        r += M * tmp;
        M *= m[i]/d;
    }
    return make_pair(mod(r, M), M);
}


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vll b(3),m(3);
  auto check=[&](){
    pll res=ChineseRem(b,m);
    if(res.se==-1)cout<<-1<<endl;
    //if b has 0,out is lcm;
    //else if(!exist_non_zero)cout<<res.se<<endl;
    else cout<<res.fi<<endl;
  };

  b={10,10,10};
  m={20,30,40};
  check();

  b={10,10,30};
  m={20,30,40};
  check();

  b={1,0,5};
  m={2,4,17};
  check();

}

