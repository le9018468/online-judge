#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
typedef pair<ll, ll> pi;
#ifdef tmd
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll INF = (ll)1e18 + 7;
const ll MOD = 1000000007;

ll t, n, d,timestamp,cnt;
string cmd,name;
struct node{
  node *l,*r;
  pii key;
  ll pri,size;
  string name;
  void pull(){
    size = 1;
    if(l)size += l->size;
    if(r)size += r->size;
  }
};

ll SIZ(node *a){
  return a?a->size:0;
}
node *merge(node *a,node *b){
  if(!a||!b)return a?a:b;
  if(a->pri < b->pri){
    a->r = merge(a->r,b);
    a->pull();
    return a;
  } else {
    b->l = merge(a,b->l);
    b->pull();
    return b;
  }
}

void split(node *o,node *&a,node *&b,pii k){//ALL(a) < k
  if(!o){
    a = 0,b = 0;
    return;
  }
  else if(o->key < k) {
    a = o;
    split(o->r,a->r,b,k);
  } else {
    b = o;
    split(o->l,a,b->l,k);
  }
  o->pull();
}



void split2(node *o,node *&a,node *&b,ll k){
  if(!o){
    a=0,b=0;
    return;
  }
  if(k >= SIZ(o->l)+1){
    a = o;
    split2(o->r,a->r,b,(k-SIZ(o->l)-1));
  } else {
    b = o;
    split2(o->l,a,b->l,k);
  }
  o->pull();
}

void ptree(node *nd){
  cout<<"LEFT "<<nd->name<<endl;
  if(nd->l)ptree(nd->l);
  cout<<"DEBUG: "<<nd->name<<" "<<nd->key.X<<" "<<nd->key.Y<<endl;
  cout<<"RIGHT "<<nd->name<<endl;
  if(nd->r)ptree(nd->r);
}

void insert(node *&root,string nm,ll val){
  cnt++;
  if(!root){
    root = new node{0,0,{val,++timestamp},rand(),1,nm};
    return;
  }
  node *a,*b;
  split(root,a,b,{val+1,-INF});
  node *tmp = merge(new node{0,0,{val,++timestamp},rand(),1,nm},b);
  root = merge(a,tmp);
}


void DEL(node *&nd){
  if(nd->l)DEL(nd->l);
  if(nd->r) DEL(nd->r);
  delete nd;
}


void find(node *&root,ll k){
  if(!root){
    debug("EAIT");
    cout<<"WAIT..."<<endl;
    return;
  }
  node *a,*b,*c;
  split(root,a,b,{k,-1});
  split2(b,b,c,1);

  if(!b){
    cout<<"WAIT..."<<endl;
    root = merge(a,c);
    return;
  } else {
    cout<<b->name<<endl;
    delete b;
    root = merge(a,c);
    cnt--;
  }


}
/********** Main()  function **********/
int main()
{
  IOS();
  cin.tie(0);
  cin>>t;
  int case_no = 0;
  while(t--){
    cout<<"Case #"<<++case_no<<":"<<endl;
    timestamp = 0;
    cnt = 0;
    node *root = 0;
    cin>>n;
    REP(i,n){
      cin>>cmd;
      if(cmd[0]=='A'){
        cin>>name>>d;
        insert(root,name,d);
        cout<<cnt<<endl;
        // if(root)ptree(root);
      } else {
        cin>>d;
        find(root,d);
        // if(root)ptree(root);
      }
    }
    if(root)DEL(root);
  }
	return 0;
}

//Treap
