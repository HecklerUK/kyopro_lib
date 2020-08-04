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


//参照
//https://ei1333.hateblo.jp/entry/2017/09/11/211011
struct Mo
{
  vector< int > left, right, order;
  vector< bool > v;
  int width;
  int nl, nr, ptr;

  Mo(int n) : width((int) sqrt(n)), nl(0), nr(0), ptr(0), v(n) {}

  void insert(int l, int r) /* [l, r) */
  {
    left.push_back(l);
    right.push_back(r);
  }

  /* ソート */
  void build()
  {
    order.resize(left.size());
    iota(begin(order), end(order), 0);
    sort(begin(order), end(order), [&](int a, int b)
    {
      if(left[a] / width != left[b] / width) return left[a] < left[b];
      return right[a] < right[b];
    });
  }

  /* クエリを 1 つぶんすすめて, クエリのidを返す */
  int process()
  {
    if(ptr == order.size()) return (-1);
    const auto id = order[ptr];
    while(nl > left[id]) distribute(--nl);
    while(nr < right[id]) distribute(nr++);
    while(nl < left[id]) distribute(nl++);
    while(nr > right[id]) distribute(--nr);
    return (order[ptr++]);
  }

  inline void distribute(int idx)
  {
    v[idx].flip();
    if(v[idx]) add(idx);
    else del(idx);
  }

  void add(int idx);

  void del(int idx);
};




int N, A[300000], Q;
int ans[200000];
int cnt[1000001], sum;

//値追加時の操作
//要素を加えるとき、cntが0ならsum(種類数)を増やす
void Mo::add(int idx)
{
  if(cnt[A[idx]]++ == 0) ++sum;
}

//値削除時の操作
void Mo::del(int idx)
{
  if(--cnt[A[idx]] == 0) --sum;
}

int main()
{
  scanf("%d", &N);
  for(int i = 0; i < N; i++) {
    scanf("%d", &A[i]);
  }
  scanf("%d", &Q);
  Mo mo(N);
  for(int i = 0; i < Q; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    mo.insert(--a, b);
  }
  mo.build();
  for(int i = 0; i < Q; i++) {
    int idx = mo.process();
    ans[idx] = sum;
  }
  for(int i = 0; i < Q; i++) {
    printf("%d\n", ans[i]);
  }
}

