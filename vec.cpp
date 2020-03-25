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


#include <complex>
typedef complex<double> P;

double dot(const P& x, const P& y){
  return real(conj(x)*y);
}

double cross(const P& x, const P& y){
  return imag(conj(x)*y);
}

int ccw(P a, P b, P c){
  b -= a;
  c -= a;
  if(cross(b, c)>0) // counter clockwise
    return 1;
  if(cross(b, c)<0) // clockwise
    return -1;
  if(dot(b, c)<0) // c--a--b on line
    return 2;
  if(norm(b) < norm(c)) // a--b--c on line
    return -2;
  return 0;
}

bool check(P a, P b, P c, P d){
  return ccw(a,b,c)*ccw(a,b,d) <= 0 && ccw(c,d,a)*ccw(c,d,b) <= 0;
}



int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  P a(1,2), b(3,4);
  cout<<"a*b:"<<dot(a, b)<<endl;
  cout<<"aXb:"<<cross(a, b)<<endl;


}
