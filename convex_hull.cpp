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


struct P{
  ld x,y;
  ld epsilon=1e-10;
  ld add(ld a, ld b){
    if(abs(a+b)<eps)
      return 0;
    return a+b;
  }

  P(){}
  P(ld x, ld y):x(x),y(y){}

  P operator + (P p){
    return P(add(x,p.x),add(y,p.y));
  }
  P operator - (P p){
    return P(add(x,-p.x),add(y,-p.y));
  }
  P operator * (ld d){
    return P(x*d,y*d);
  }
  ld dot (P p){
    return add(x*p.x,y*p.y);
  }
  ld det (P p){
    return add(x*p.y,y*-p.x);
  }

};

bool compare_p(const P& p, const P& q){
  if(p.x!=q.x)
    return p.x<q.x;
  return p.y<q.y;
}

vector<P> convex_hull(P* ps, ll n){
  sort(ps, ps+n, compare_p);
  //vertex num
  ll k=0;
  vector<P> qs(n*2);

  //downer part
  for(ll i=0; i<n; i++){
    while(k>1 && (qs[k-1]-qs[k-2]).det(ps[i]-qs[k-1])<=0)
      k--;
    qs[k++]=ps[i];
  }

  //upper part
  for(ll i=n-2,t=k; i>=0; i--){
    while(k>t && (qs[k-1]-qs[k-2]).det(ps[i]-qs[k-1])<=0)
      k--;
    qs[k++]=ps[i];
  }

  qs.resize(k-1);
  return qs;
}

ld dist(P p, P q){
  return (p-q).dot(p-q);
}


//find max distance P pair
ld casperMethod(P* ps, ll np){
  vector<P> qs=convex_hull(ps,np);

  ll n=qs.size();
  if(n==2){
    return dist(qs[0],qs[1]);
  }

  //ある方向に最も遠い点対
  ll i=0,j=0;
  //X軸方向に最も遠い点対を求める
  for(ll k=0; k<n; k++){
    if(!compare_p(qs[i],qs[k]))
      i=k;
    if(compare_p(qs[j],qs[k]))
      j=k;
  }

  ld res=0;
  ll si=i,sj=j;
  while(i!=sj || j!=si){
    res=max(res,dist(qs[i],qs[j]));
    //i-(i+1)とj-(j+1)のどちらの法線方向を先に向くか判定
    if((qs[(i+1)%n]-qs[i]).det(qs[(j+1)%n]-qs[j])<0)
      i=(i+1)%n;
    else
      j=(j+1)%n;
  }

  return res;
}



const ll MAX_N=1e5;
ll N;
P ps[MAX_N];


int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n=4;
  ps[0]=P(0,0);
  ps[1]=P(1,0);
  ps[2]=P(0,1);
  ps[3]=P(1,1);


  ld adist=casperMethod(ps,n);
  ld p=sqrt(adist);
  cout<<Decimal;
  cout<<p<<endl;

}

