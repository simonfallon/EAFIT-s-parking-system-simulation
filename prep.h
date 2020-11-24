#ifndef PREP_H
#define PREP_H

#include "global.h"

void floyd_warshall(){
  forn(k, 6)
    forn(i, 6)
      forn(j, 6)
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

void create_graph(){          ///tested!
  forn(i, 6){
    forn(j, 6)
      d[i][j] = inf;
    d[i][i] = 0;
    d[i][(i+1)%6] = tran[i];
  }
  d[4][0] = tran[6];
  floyd_warshall();
}

string to_time_min(int idx, int ids){         ///tested!
   int hour = 5 + idx/60;
   int minu = idx%60;
   string h = to_string(hour);
   string m = to_string(minu);
   if(sz(m) == 1) m = '0' + m;
   if(sz(h) == 1) h = '0' + h;
   if(ids == 1) return h + ':' + m + ':' + "00";
   else         return h + ':' + m;
}

string to_time_seg(int idx, int ids){         ///tested!
  if(idx < 0) return "3:00:00";
  if(ids == 2 && idx == 0) return "4:00:00";
  int hour = 5 + idx/3600;
  if(ids >= 2) hour -= 5;
  int minu = (idx%3600)/60;
  int seg  = idx%60;
  string h = to_string(hour);
  string m = to_string(minu);
  string s = to_string(seg);
  if(sz(m) == 1) m = '0' + m;
  if(sz(h) == 1) h = '0' + h;
  if(sz(s) == 1) s = '0' + s;
  if(ids==1 || ids==3) return h + ':' + m + ':' + s;
  else         return h + ':' + m;
}

void gen_time(){              ///tested!
  forn(i, 10){
    if(i < 9) t[i] = to_time_min(60 + i*90, 0);
    else      t[i] = to_time_min(150 + i*90, 0);
  }
  forn(i, 21){
    int l = (i == 0 ? 0 : ub_in[i-1]);
    int r = ub_in[i];
    tt_in[i].fi = to_time_seg(l, 0);
    tt_in[i].se = to_time_seg(r, 0);
  }
  forn(i, 21){
    int l = (i == 0 ? 0 : ub_out[i-1]);
    int r = ub_out[i];
    tt_out[i].fi = to_time_seg(l, 0);
    tt_out[i].se = to_time_seg(r, 0);
  }
}

void test_graph(){
  cout<<el<< "--------TESTING GRAPH--------"<<el<<el;
  forn(i, 6){
    cout << "Source = " << f_name[i] <<el<<"Destinations:"<<el;
    forn(j, 6){
      if(i==j) continue;
      cout << f_name[j] << ": " << to_time_seg(d[i][j], 3) << el;
    }
    cout << el;
  }
}

void pre(bool test = false){                   ///tested!
  forn(i, 10){
    if(big.count(i))   b[i] = true;
    if(small.count(i)) s[i] = true;
  }
  forn(i, 10){
    if(b[i])  bb[id_in[i]] = true;
    if(s[i])  ss[id_in[i]] = true;
  }
  forn(i, 21){
    flow_in[i] = 0.0;
    forn(j, 21){
      flow[i][j] = 0.0;
      prob[i][j] = 0.0;
    }
  }
  gen_time();
  create_graph();
  if(test)
    test_graph();
}

#endif // PREP_H
