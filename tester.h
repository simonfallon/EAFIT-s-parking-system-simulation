#ifndef TESTER_H
#define TESTER_H

#include "auxiliar.h"

void test_in(){          ///T!
  cout <<el<< "--------TESTING INCOMING FLOW GENERATOR--------"<<el<<el;
  double total_out = 0, total_big = 0, total_small = 0;
  forn(i, 21){
    cout<<"i = "<<i;
    if(i<10) cout<<" ";
    cout <<": "<<tt_in[i].fi<<" - "<<tt_in[i].se<<",  flow_in[i] = "<<flow_in[i] << " %"<<el;
    if(ss[i])      total_small += flow_in[i];
    else if(bb[i]) total_big   += flow_in[i];
    else           total_out   += flow_in[i];
  }
  cout << "total_big = " << total_big<<" %"<< el;
  cout << "total_small = " << total_small<<" %"<< el;
  cout << "total_out = " << total_out<<" %"<< el;
}

void test_lambda_in(int idx){    ///T!
  cout<<el << "Testing lambda_in for fila #" << idx <<" (" << f_name[idx]<<"):"<<el;
  if(idx>=6 || idx<0) {
    cout << "Invalid input"<<el;
    return;
  }
  cout << setprecision(5);
  forn(i, 21){
    cout<<"i = "<<i;
    if(i<10) cout<<" ";
    cout <<": "<<tt_in[i].fi<<" - "<<tt_in[i].se<<", l_in[i] =  "<<l_in[idx][i] << el;
  }
  cout << el<< setprecision(3);
}

void test_lambda_out(int idx){  ///T!
  cout << el << "Testing lambda_out for park #" << idx <<" (" << p_name[idx]<<"):"<<el;
  if(idx>=4 || idx<0) {
    cout << "Invalid input"<<el;
    return;
  }
  cout << setprecision(5);
  forn(i, 21){
    cout<<"i = "<<i;
    if(i<10) cout<<" ";
    cout <<": "<<tt_out[i].fi<<" - "<<tt_out[i].se<<", l_out[i] =  "<< l_out[idx][i] << el;
  }
  cout << el << setprecision(3);
}

void test_big(){        ///T!
  cout << el << "-------TESTING FLOW_DISTRIBUTION FOR BIG-------" <<el<<el;
    forn(i, 9){
      if(s[i]) continue;
      int ii = id_in[i];
      cout << "i: " << ii << ",  Hora de entrada t[i] = "<< tt_in[ii].fi << " - "<<tt_in[ii].se << el;
      double sum = 0, sum_s = 0, sum_b = 0, sum_o = 0;
      cout << "Porcentaje de flujo salidas:" << el;
      fore(j, ii+1, 20){
        cout<<"j = "<<j;
        if(j<10) cout << " ";
        cout<<", t[j] = "<<tt_out[j].fi<<" - "<<tt_out[j].se<<" : "<< flow[ii][j]<<" %"<<el;
        sum += flow[ii][j];
        if(ss[j])       sum_s += flow[ii][j];
        else if(bb[j])  sum_b += flow[ii][j];
        else            sum_o += flow[ii][j];
      }
      cout<<"sum = "<<sum <<" %, sum_b = "<<sum_b<<" %, sum_s = ";
      cout<< sum_s<<" %, sum_o = "<< sum_o <<" %"<< el << el ;
    }
}

void test_small(){      ///T!
  cout << el << "-------TESTING FLOW_DISTRIBUTION FOR SMALL-------" <<el<<el;
    forn(i, 9){
      if(b[i]) continue;
      int ii = id_in[i];
      cout << "i: " << ii << ",  Hora de entrada t[i] = "<< tt_in[ii].fi << " - "<<tt_in[ii].se<<el;
      double sum = 0, sum_s = 0, sum_b = 0, sum_o = 0;
      cout << "Porcentaje de flujo salidas:" << el;
      fore(j, ii+1, 20){
        cout<<"j = "<<j;
        if(j<10) cout << " ";
        cout<<", t[j] = "<<tt_out[j].fi<<" - "<<tt_out[j].se<<" : "<< flow[ii][j]<<" %"<<el;
        sum += flow[ii][j];
        if(ss[j])       sum_s += flow[ii][j];
        else if(bb[j])  sum_b += flow[ii][j];
        else            sum_o += flow[ii][j];
      }
      cout<<"sum = "<<sum <<" %, sum_b = "<<sum_b<<" %, sum_s = ";
      cout<< sum_s<<" %, sum_o = "<< sum_o<<" %" << el << el ;
    }
}

void test_out(){        ///T!
  cout << el << "------------TESTING FLOW_DISTRIBUTION FOR OUT-------" <<el<<el;
    for1(i, 18){
      if(!is_out(i)) continue;
      cout << "i: " << i << ", Hora de entrada  t[i] = "<< tt_in[i].fi << " - "<<tt_in[i].se << el;
      double sum = 0, sum_s = 0, sum_b = 0, sum_o = 0;
      cout << "Porcentaje de flujo salidas:" << el;
      fore(j, i+1, 20){
        cout<<"j = "<<j;
        if(j<10) cout << " ";
        cout<<", t[j] = "<<tt_out[j].fi<<" - "<<tt_out[j].se<<" : "<<flow[i][j]<<" %"<<el;
        sum += flow[i][j];
        if(ss[j])       sum_s += flow[i][j];
        else if(bb[j])  sum_b += flow[i][j];
        else            sum_o += flow[i][j];
      }
      cout<<"sum = "<<sum <<" %, sum_b = "<<sum_b<<" %, sum_s = ";
      cout<< sum_s<<" %, sum_o = "<< sum_o<<" %" << el << el ;
    }
}

void compare_lambda_in_idx(int idx){  ///T!
  if(idx>=6 || idx<0) {
    cout << "Invalid input (compare_l_in_idx)"<<el;
    return;
  }
  cout<<el << "Comparing fila #" << idx <<" (" << f_name[idx]<<"):"<<el;
  cout << setprecision(5);
  forn(i, 21){
    cout<<"i = "<<i;
    if(i<10) cout<<" ";
    cout <<": "<<tt_in[i].fi<<" - "<<tt_in[i].se<<", l_in_teo[i] =  ";
    cout<<l_in[idx][i]<<" - l_in_real[i] = "<< l_in_real[idx][i]<< el;
  }
  cout << el<< setprecision(3);
}

void compare_lambda_in(){             ///T!
  cout << el << "-------COMPARING LAMDA_IN TEO. VS LAMBDA_IN REAL-------" << el<<el;
  forn(i, 6){
    compare_lambda_in_idx(i);
  }
}

void compare_lambda_out_idx(int idx){ ///T!
  if(idx>=4 || idx<0) {
    cout << "Invalid input (compare_lambda_out_idx)"<<el;
    return;
  }
  cout<<el << "Comparing park #" << idx <<" (" << p_name[idx]<<"):"<<el;
  cout << setprecision(5);
  forn(i, 21){
    cout<<"i = "<<i;
    if(i<10) cout<<" ";
    cout <<": "<<tt_out[i].fi<<" - "<<tt_out[i].se<<", l_out_teo[i] =  ";
    cout<<l_out[idx][i]<<" - l_out_real[i] = "<< l_out_real[idx][i]<< el;
  }
  cout << el<< setprecision(3);
}

void compare_lambda_out(){            ///T!
  cout << el << "-------COMPARING LAMDA_OUT TEO. VS LAMBDA_OUT REAL-------" << el<<el;
  forn(i, 4){
    compare_lambda_out_idx(i);
  }
}

void compare_l_out_idx(int idx){      ///T!
  if(idx>=4 || idx<0) {
    cout << "Invalid input (compare_l_out_idx)"<<el;
    return;
  }
  cout<<el << "Comparing park #" << idx <<" (" << p_name[idx]<<"):"<<el;
  cout << setprecision(5);
  forn(i, 21){
    cout<<"i = "<<i;
    if(i<10) cout<<" ";
    cout <<": "<<tt_out[i].fi<<" - "<<tt_out[i].se<<", l_out_real[i] = ";
    cout<<l_out_real[idx][i]<<" - l_out_exp[i] = "<< l_out_exp[idx][i]<< el;
  }
  cout << el<< setprecision(3);
}

void compare_l_out(){                 ///T!
  cout << el << "-------COMPARING LAMDA_OUT REAL. VS LAMBDA_OUT EXPECTED-------" << el<<el;
  forn(i, 4){
    compare_l_out_idx(i);
  }
}

void test_arrivals_idx(int idx, bool test = false){   ///MELO!
  total_arr[idx].assign(21, 0);
  forn(i, sz(entries[idx])){
    forn(j, 21){
      int l = (j == 0 ? 0 : ub_in[j-1]);
      int r = ub_in[j];
      if(l <= entries[idx][i].arr_t && entries[idx][i].arr_t <= r){
        total_arr[idx][j]++;
        break;
      }
    }
  }
  int total = 0;
  if(test){
    cout <<el<< "Testing arrivals for queue #" << idx << " (" << f_name[idx] <<"):"<< el;
    forn(i, 21){
      cout <<"i = "<<i;
      if(i < 10) cout << " ";
      cout <<" : "<< tt_in[i].fi << " - " << tt_in[i].se;
      cout <<":  arr = " << total_arr[idx][i] << el;
      total += total_arr[idx][i];
    }
    cout << "Total arrivals = " << total << el;
  }
}

void test_arrivals(bool test = false){     ///MELO!
  if(test){
    cout <<el<< "-----TESTING FULL-DAY ARRIVALS GENERATOR-----"<<el<<el;
    int total = 0;
    cout << "Total arrivals by entry" << el;
    forn(i, 6) {
      total += cur_sz[i];
      cout << i << ": " << cur_sz[i]  << " ("<< f_name[i] << ")"<< el;
    }
    d(total);
  }
  vector<int> total_p(4, 0);
  forn(i, 6)
    total_p[p_id[i]] += cur_sz[i];
  if(test){
    cout << el << "Total arrivals by park" << el;
    forn(i, 4)
      cout << i << ": " << total_p[i]  << " ("<< p_name[i] << ")"<< el;
  }
  forn(i, 6)
    test_arrivals_idx(i);
}

void test_exits_idx(int idx){              ///MELO!
  forn(i, sz(entries[idx])){
    forn(j, 21){
      int l = (j == 0 ? 0 : ub_out[j-1]);
      int r = ub_out[j];
      if(l <= entries[idx][i].ex_t && entries[idx][i].ex_t <= r){
        total_exits[p_id[idx]][j]++;
        break;
      }
    }
  }
}

void test_exp_exits_idx(int idx){          ///MELO!
  forn(i, sz(entries[idx])){
    forn(j, 21){
      int l = (j == 0 ? 0 : ub_out[j-1]);
      int r = ub_out[j];
      if(l <= entries[idx][i].exp_ex_t && entries[idx][i].exp_ex_t <= r){
        total_exp_exits[p_id[idx]][j]++;
        break;
      }
    }
  }
}

void test_exits(bool compare = false){     ///MELO!
  forn(i, 4) {
    total_exits[i].assign(21, 0);
    total_exp_exits[i].assign(21, 0);
  }
  forn(i, 6){
    test_exits_idx(i);
    test_exp_exits_idx(i);
  }

  cout <<el<< "-----TESTING FULL-DAY EXITS GENERATOR-----"<<el<<el;
  int total = 0, total_p;

  cout << "Total exits by park" << el;
  forn(i, 4) {
    total_p = 0;
    forn(j, 21)
      total_p += total_exits[i][j];
    cout << i << ": " << total_p  << " ("<< p_name[i] << ")"<< el;
    total += total_p;
  }
  d(total);

  forn(idx, 4){
    total_p = 0;
    cout <<el<< "Testing exits for park #" << idx << " (" << p_name[idx] <<"):"<< el;
    forn(i, 21){
      cout <<"i = "<<i;
      if(i < 10) cout << " ";
      cout <<" : "<< tt_out[i].fi << " - " << tt_out[i].se;
      cout <<":  exits = " << total_exits[idx][i] << el;
      total_p += total_exits[idx][i];
    }
    cout << "Total exits = " << total_p << el;
  }
}

#endif // TESTER_H
