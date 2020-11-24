#ifndef AUXILIAR_H
#define AUXILIAR_H

#include "prep.h"

void normalize(double &big, double &small, double &out, bool test){ ///tested!
  double rest = 100.0 - out;
  big *= (rest/100.0);  small *= (rest/100.0);
  if(test)
    cout <<el<<"big = "<<big <<",  small = "<<small << ", out = " <<out <<el;
}

int len_in(int i){            ///tested!
  return ub_in[i] - (i == 0 ? 0 : ub_in[i-1]);
}

int len_out(int i){           ///tested!
  return ub_out[i] - (i == 0 ? 0 : ub_out[i-1]);
}

bool is_out(int i){           ///tested!
  return (!ss[i] && !bb[i]);
}

int sz_big(int i){            ///tested!
  int cnt = 0;
  fore(j, i+1, 9)
    if(b[j]) cnt++;
  return cnt;
}

int sz_small(int i){          ///tested!
  int cnt = 0;
  fore(j, i+1, 9)
    if(s[j]) cnt++;
  return cnt;
}

int sz_out(int i){            ///tested!
  int cnt = 0;
  fore(j, i+1, 20)
    if(is_out(j)) cnt++;
  return cnt;
}

void fill_flow(int i, double p_b, double p_s){    ///tested!
  int ii = id_in[i];
  fore(j, i+1, 9){
    int jj = id_in[j];
    if(b[j])
      flow[ii][jj] = p_b;
    if(s[j])
      flow[ii][jj] = p_s;
  }
}

void fill_flow_2(int i, double p_b, double p_s){  ///tested!
  int ii = r_id[i];
  fore(j, ii+1, 9){
    int jj = id_in[j];
    if(b[j])
      flow[i][jj] = p_b;
    if(s[j])
      flow[i][jj] = p_s;
  }
}

void fill_flow_bounded(int i, double p_b, double p_s, int sz_b, int sz_s){
  int ii = id_in[i];
  fore(j, i+1, 9){
    int jj = id_in[j];
    if(b[j] && sz_b){
      flow[ii][jj] = p_b;
      sz_b--;
    }
    if(s[j] && sz_s){
      flow[ii][jj] = p_s;
      sz_s--;
    }
  }
}

void fill_flow_bounded_2(int i, double p_b, double p_s, int sz_b, int sz_s){  ///tested!
  int ii = r_id[i];
  fore(j, ii+1, 9){
    int jj = id_in[j];
    if(b[j] && sz_b){
      flow[i][jj] = p_b;
      sz_b--;
    }
    if(s[j] && sz_s){
      flow[i][jj] = p_s;
      sz_s--;
    }
  }
}


vector<double> normal_cdf(int n_inter, bool test = false){
  vector<double> ans(n_inter);

  if(n_inter == 0){
    return ans;
  }

  vector<int> idx(n_inter);
  double sum = 0;
  forn(i, n_inter){
    idx[i] = 999*(i+1)/n_inter;
    if(i == 0)
      ans[i] = p_norm[idx[i]];
    else
      ans[i] = (p_norm[idx[i]] - p_norm[idx[i-1]]);
    sum += ans[i];
  }

  if(test){
    forn(i, n_inter)
      cout<< "idx = "<< idx[i]<< ":  F(idx) = "<< ans[i]<<el;
    d(sum);
  }
  return ans;
}


void fill_flow_normal_b(int i, double p_b, double p_s, double p_o, int sz_b, int sz_s, int sz_o){
  vector<double> norm_cdf_b = normal_cdf(sz_b);
  vector<double> norm_cdf_s = normal_cdf(sz_s);
  vector<double> norm_cdf_o = normal_cdf(sz_o);
  int i_b = 0, i_s = 0, i_o = 0;

  int ii = id_in[i];
  fore(j, i+1, 9){
    int jj = id_in[j];
    if(b[j] && i_b < sz_b)
      flow[ii][jj] = p_b * norm_cdf_b[i_b++];

    if(s[j] && i_s < sz_s)
      flow[ii][jj] = p_s * norm_cdf_s[i_s++];
  }
  fore(j, ii+1, 20){
    if(is_out(j) && i_o < sz_o)
      flow[ii][j] = p_o * norm_cdf_o[i_o++];
  }
}

void fill_flow_normal_b_2(int i, double p_b, double p_s, double p_o, int sz_b, int sz_s, int sz_o){
  vector<double> norm_cdf_b = normal_cdf(sz_b);
  vector<double> norm_cdf_s = normal_cdf(sz_s);
  vector<double> norm_cdf_o = normal_cdf(sz_o);
  int i_b = 0, i_s = 0, i_o = 0;

  int ii = r_id[i];
  fore(j, ii+1, 9){
    int jj = id_in[j];
    if(b[j] && i_b < sz_b)
      flow[i][jj] = p_b * norm_cdf_b[i_b++];

    if(s[j] && i_s < sz_s)
      flow[i][jj] = p_s * norm_cdf_s[i_s++];
  }
  fore(j, i+1, 20){
    if(is_out(j) && i_o < sz_o)
      flow[i][j] = p_o * norm_cdf_o[i_o++];
  }
}

#endif // AUXILIAR_H
