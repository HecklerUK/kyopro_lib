#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef vector<ll> vll;
typedef vector<vll> vvll;
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


struct SegmentTreeMAX{
  ll n;
  vll tree;

  SegmentTreeMAX(ll len){
    n=1;
    while(len>n)
      n*=2;

    tree.assign(2*n-1, -LLINF);
  }

  void update(ll index, ll value){
    index += n-1;
    tree[index] = value;

    while(index>0){
      index=(index-1)/2;
      tree[index] = max(tree[index*2+1], tree[index*2+2]);
    }
  }


  //[a, b)
  ll query(ll a, ll b){
    return query(a,b,0,0,n);
  }

  ll query(ll a, ll b, ll index, ll l, ll r){
    if(b<=l || r<=a)
      return -LLINF;

    if(a<=l && r<=b)
      return tree[index];

    ll value_l = query(a,b,2*index+1,l,(l+r)/2);
    ll value_r = query(a,b,2*index+2,(l+r)/2,r);
    return max(value_l, value_r);
  }
};



struct SegmentTreeMIN{
  ll n;
  vll tree;

  SegmentTreeMIN(ll len){
    n=1;
    while(len>n)
      n*=2;

    tree.assign(2*n-1, LLINF);
  }

  void update(ll index, ll value){
    index += n-1;
    tree[index] = value;

    while(index>0){
      index=(index-1)/2;
      tree[index] = min(tree[index*2+1], tree[index*2+2]);
    }
  }


  //[a, b)
  ll query(ll a, ll b){
    return query(a,b,0,0,n);
  }

  ll query(ll a, ll b, ll index, ll l, ll r){
    if(b<=l || r<=a)
      return LLINF;

    if(a<=l && r<=b)
      return tree[index];

    ll value_l = query(a,b,2*index+1,l,(l+r)/2);
    ll value_r = query(a,b,2*index+2,(l+r)/2,r);
    return min(value_l, value_r);
  }
};

//区間和
struct SegmentTreeSUM{
  ll n;
  vll tree;

  SegmentTreeSUM(ll len){
    n=1;
    while(len>n)
      n*=2;

    tree.assign(2*n-1, 0);
  }

  void update(ll index, ll value){
    index += n-1;
    tree[index] = value;

    while(index>0){
      index=(index-1)/2;
      tree[index] = tree[index*2+1]+tree[index*2+2];
    }
  }


  //[a, b)
  ll query(ll a, ll b){
    return query(a,b,0,0,n);
  }

  ll query(ll a, ll b, ll index, ll l, ll r){
    if(b<=l || r<=a)
      return 0;

    if(a<=l && r<=b)
      return tree[index];

    ll value_l = query(a,b,2*index+1,l,(l+r)/2);
    ll value_r = query(a,b,2*index+2,(l+r)/2,r);
    return value_l+value_r;
  }
};


//区間加算
template<typename T> 
struct SegmentTreeADD{
  ll n;
  vector<T> tree[2];

  SegmentTreeADD(ll len){
    n=1;
    while(len>n)
      n*=2;

    REP(i,2)
      tree[i].assign(2*n-1, 0);
  }

  void set(ll index, T x){
    tree[0][n-1+index]=x;
  }

  void build(){
    for(int index=n-2; index>=0; index--)
      tree[0][index] = tree[0][index*2+1]+tree[0][index*2+2];
  }


  //[a, b)
  void add(ll a, ll b, T x){
    return add(a,b,x,0,0,n);
  }

  void add(ll a, ll b, T x, ll index, ll l, ll r){
    if(a<=l && r<=b)
      tree[1][index]+=(r-l)*x;

    else if(l<b && a<r){
      tree[1][index]+=(min(b,r)-max(a,l))*x;
      add(a,b,x,2*index+1,l,(l+r)/2);
      add(a,b,x,2*index+2,(l+r)/2,r);
    }
  }

  //[a, b)
  T sum(ll a, ll b){
    return sum(a,b,0,0,n);
  }

  T sum(ll a, ll b, ll index, ll l, ll r){
    if(b<=l || r<=a)
      return 0;

    else if(a<=l && r<=b)
      return tree[0][index]+tree[1][index];

    else{
      ll res=0;
      res += sum(a,b,2*index+1,l,(l+r)/2);
      res += sum(a,b,2*index+2,(l+r)/2,r);
      return res;
    }
  }


};



int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vll v={2,3,6,1,8,4,7};
  ll n=v.size();

//  SegmentTreeMAX st(n);
//  REP(i,n)
//    st.update(i,v[i]);
//
//  ll ans=st.query(1,5);
//  cout<<ans<<endl;
  SegmentTreeADD<ll> st(n);
  REP(i,n)st.set(i,v[i]);
  st.build();
  REP(i,n)
    cout<<"tree:"<<st.tree[0][7+i]<<endl;
  cout<<st.sum(0,7)<<endl;

  st.add(2,6,1);
  cout<<st.sum(0,7)<<endl;
}
