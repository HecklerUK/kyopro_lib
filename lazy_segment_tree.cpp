
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

//
// Segment Tree
// https://ei1333.github.io/algorithm/segment-tree.html
template< typename Monoid, typename OperatorMonoid = Monoid >
struct LazySegmentTree
{
  using F = function< Monoid(Monoid, Monoid) >;
  using G = function< Monoid(Monoid, OperatorMonoid) >;
  using H = function< OperatorMonoid(OperatorMonoid, OperatorMonoid) >;
  using P = function< OperatorMonoid(OperatorMonoid, int) >;

  int sz;
  vector< Monoid > data;
  vector< OperatorMonoid > lazy;
  const F f; //2つの要素をマージする二項演算
  const G g; //要素と作用素のマージ
  const H h; //作用素と作用素のマージ
  const P p; //作用素を下に降ろすときに行う演算
  //(第一引数は作用素のもとの値, 第二引数は降ろした後の区間の長さ)
  const Monoid M1; //要素の単位元
  const OperatorMonoid OM0; //作用素の単位元



  //SegTreeLazyProportional<X,M>(n,fx,fa,fm,fp,ex,em):
  //モノイド(集合X, 二項演算fx,fa,fm,p 単位元ex,em)についてサイズnで構築
  LazySegmentTree(int n, const F f, const G g, const H h, const P p,
                  const Monoid &M1, const OperatorMonoid OM0)
      : f(f), g(g), h(h), p(p), M1(M1), OM0(OM0)
  {
    sz = 1;
    while(sz < n) sz <<= 1;
    data.assign(2 * sz, M1);
    lazy.assign(2 * sz, OM0);
  }

  //set(int i, X x), build(): i番目の要素をxにセット。
  //まとめてセグ木を構築する。O(n)
  void set(int k, const Monoid &x)
  {
    data[k + sz] = x;
  }

  void build()
  {
    for(int k = sz - 1; k > 0; k--) {
      data[k] = f(data[2 * k + 0], data[2 * k + 1]); //1-indexed
    }
  }

  //lazy eval O(1)
  void propagate(int k, int len)
  {
    if(lazy[k] != OM0) { //更新するものが無ければ終了
      if(k < sz) { //葉でなければ子に伝搬
        lazy[2 * k + 0] = h(lazy[2 * k + 0], lazy[k]);
        lazy[2 * k + 1] = h(lazy[2 * k + 1], lazy[k]);
      }
      //自身を更新
      data[k] = g(data[k], p(lazy[k], len));
      lazy[k] = OM0;
    }
  }

  Monoid update(int a, int b, const OperatorMonoid &x, int k, int l, int r)
  {
    propagate(k, r - l);
    if(r <= a || b <= l) { //完全に外側の時
      return data[k];
    } else if(a <= l && r <= b) { //完全に内側の時
      lazy[k] = h(lazy[k], x);
      propagate(k, r - l);
      return data[k];
    } else { //一部区間がかぶる時
      return data[k] = f(update(a, b, x, 2 * k + 0, l, (l + r) >> 1),
                         update(a, b, x, 2 * k + 1, (l + r) >> 1, r));
    }
  }

  //update(a,b,x): [a,b) 番目の要素を Monoid x に更新。O(log(n))
  Monoid update(int a, int b, const OperatorMonoid &x)
  {
    return update(a, b, x, 1, 0, sz);
  }


  Monoid query(int a, int b, int k, int l, int r)
  {
    propagate(k, r - l);
    if(r <= a || b <= l) { //完全に外側の時
      return M1;
    } else if(a <= l && r <= b) { //完全に内側の時
      return data[k];
    } else { //一部区間がかぶる時
      return f(query(a, b, 2 * k + 0, l, (l + r) >> 1),
               query(a, b, 2 * k + 1, (l + r) >> 1, r));
    }
  }

  //query(a,b):  [a,b) 全てにfxを作用させた値を取得。O(log(n))
  Monoid query(int a, int b)
  {
    return query(a, b, 1, 0, sz);
  }

  Monoid operator[](const int &k)
  {
    return query(k, k + 1);
  }
};


#include <bits/stdc++.h>
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




int main(){
  ll N=7;

  //f: X × X → X
  //g: X × M → X
  //h: M × M → M
  //p: M × N → M
  //ex: モノイドXでの単位元
  //em: モノイドMでの単位元
   //区間 addをした後区間 minを取りたい
  {
    cout<<"test1"<<endl;
    auto f = [](ll x1, ll x2) { return min(x1, x2); };
    auto g = [](ll x, ll m) { return x+m; };
    auto h = [](ll m1, ll m2) { return m1+m2; };
    auto p = [](ll m, ll n) { return m; };
    ll ex = 1e9;
    ll em = 0;
    LazySegmentTree<ll> seg(N, f, g, h, p, ex, em);
     REP(i,7)seg.set(i,7-i);
    seg.build();

    assert(seg.query(0,7)==1);
    seg.update(5,7,10);
    assert(seg.query(0,7)==3);
  }


  //f: X × X → X
  //g: X × M → X
  //h: M × M → M
  //p: M × N → M
  //ex: モノイドXでの単位元
  //em: モノイドMでの単位元
  //区間を定数に更新した後区間minを取りたい
  //区間更新はminな方にしたい(h)
  {
    cout<<"test2"<<endl;
    auto f = [](ll x1, ll x2) { return min(x1, x2); };
    auto g = [](ll x, ll m) { return m; };
    auto h = [](ll m1, ll m2) { return min(m1,m2); };
    auto p = [](ll m, ll n) { return m; };
    ll ex = 1e9;
    ll em = LLINF;
    LazySegmentTree<ll> seg(N, f, g, h, p, ex, em);
    REP(i,7)seg.set(i,7-i);
    seg.build();

    assert(seg.query(0,7)==1);
    seg.update(5,7,4);
    assert(seg.query(0,7)==3);
    assert(seg.query(5,7)==4);
  }



}


