#ifndef GENERATOR_H
#define GENERATOR_H

#include "tester.h"


/// --------------- RANDOM GENERATORS ------------------- ///
int gen_arr(exp_dist &dist_n){              ///tested!
   return max(1, int(ceil(dist_n(gen))));
}

int gen_exit(exp_dist &dist_m){             ///tested!
   return max(1, int(ceil(dist_m(gen))));
}

int gen_error(norm_dist &dist_norm){        ///tested!
  return round(dist_norm(gen));
}

double get_rand(){
  return ((double) rand() / (RAND_MAX));
}

void gen_lambda_in(bool test = false){      ///tested!
  forn(i, 4)
    cin >> ent_park[i];

  total_fila[0] = ent_park[0]/2;   total_fila[3] = ent_park[0]/2;
  total_fila[1] = ent_park[1]/2;   total_fila[2] = ent_park[1]/2;
  total_fila[4] = ent_park[2];
  total_fila[5] = ent_park[3];

  forn(i, 6){     ///for each entry
    forn(j, 21)         ///for each time interval
      l_in[i][j] = total_fila[i]*(flow_in[j]/100.0)/len_in(j);
  }
  if(test){
    cout <<el<< "--------TESTING L_IN GENERATOR--------"<<el<<el;
    forn(i, 6)
      test_lambda_in(i);
  }
}

void gen_lambda_out(bool test = false){
  forn(i, 4){     ///for each park
    forn(j, 21)     ///for each time-interval
      l_out[i][j] = double(sz(exits[i][j]))/len_out(j);
  }
  if(test){
    forn(i, 4)
      test_lambda_out(i);
  }
}

void gen_dist_in(){       ///tested!
  forn(i, 6){      ///for each fila
    forn(j, 21){        ///for each time inter.
      exp_dist di(l_in[i][j] + 0.001);        ///avoid lambda = 0
      dist_in[i][j] = di;
    }
  }
}

void gen_dist_out(){      ///tested!
  forn(i, 4){      ///for each park
    forn(j, 21){        ///for each time inter.
      exp_dist di(l_out[i][j] + 0.001);        ///avoid lambda = 0
      dist_out[i][j] = di;
    }
  }
}

void gen_prob_flow(){     ///tested!
  forn(i, 21){
    prob[i][0] = flow[i][0];
    for1(j, 20)
      prob[i][j] = prob[i][j-1] + flow[i][j];
    prob[i][20] = 100.0;
  }
}


/// ---------------- GENERATOR METHODS ------------------ ///

void gen_arrivals_file(string name, double &big, double &small, double &out, bool test = false){ ///tested!
  double real_b = big, real_s = small, w;
  normalize(real_b, real_s, out, test);

  const char *nam = name.c_str();
  freopen(nam, "r", stdin);

  forn(i, 5){       ///big
    cin >> w;
    flow_in[id_in[2*i]] = w*real_b/100.0;
  }
  forn(i, 4){       ///small
    cin >> w;
    flow_in[id_in[2*i+1]] = w*real_s/100.0;
  }
  int total_out = 0;
  for1(i, 19){
    if(is_out(i))
      total_out += len_in(i);
  }
  for1(i, 19){      ///distribute out (low intensity intervals)
    if(is_out(i))
      flow_in[i] = out*len_in(i)/total_out;
  }
  if(test) test_in();
}

void gen_arrivals(string name, double &big, double &small, double &out, bool test = false){      ///tested!
  if(name == "uniform"){
    gen_arrivals_file("A_unif.txt", big, small, out, test);
  } else if(name == "normal"){
    int sz_b = 5, sz_s = 4, sz_o = 0;
    vector<double> norm_cdf_b = normal_cdf(sz_b);
    vector<double> norm_cdf_s = normal_cdf(sz_s);

    int i_b = 0, i_s = 0, i_o = 0;

    forn(i, 5)       ///big
      flow_in[id_in[2*i]] = big * norm_cdf_b[i_b++];

    forn(i, 4)       ///small
      flow_in[id_in[2*i+1]] = small * norm_cdf_s[i_s++];

    for1(i, 19)
      if(is_out(i)) sz_o++;

    vector<double> norm_cdf_o = normal_cdf(sz_o);

    for1(i, 19)
      if(is_out(i))
        flow_in[i] = out * norm_cdf_o[i_o++];

    if(test) test_in();
    freopen("A_normal.txt", "r", stdin);
  }
}


void gen_entries(double p_app, bool test = false){                                        ///tested!
  gen_lambda_in();      ///generar lambdas_in
  gen_dist_in();        ///generar dist_in

  forn(i, 6){     ///para cada fila
    int cur_time = 2400;          ///05:00 am (begin)
    while(cur_time < ent_sz){               ///GEN. arrivals complete day
      int idx = upper_bound(all(ub_in), cur_time) - ub_in.begin();    ///IDX: TIME-INTERVAL
      int new_arr = gen_arr(dist_in[i][idx]);
      cur_time += new_arr;
      if(cur_time < ent_sz) {
        double ra = get_rand();
        entries[i].push_back(user(cur_sz[i]++, i, p_id[i], cur_time, (ra <= p_app), (i==0 || i==3)));
      }
    }
  }
  test_arrivals();
}


void gen_big(string &dist, double &big, double &small, double &out, int upper_b, bool test = false){          ///tested!
  if(dist == "uniform"){
    forn(i, 9){
      if(b[i]){///big
        int ii = id_in[i];
        int sz_b = sz_big(i);
        int sz_s = sz_small(i);
        int sz_o = sz_out(ii);
        double p_b = big/sz_b, p_s = small/sz_s, p_o = out/sz_o;
        if(sz_s == 0)  {    ///18:00 --> no more small
          p_b = (big + small)/sz_b;
        }
        fill_flow(i, p_b, p_s);
        fore(j, ii+1, 20)
          if(is_out(j)) flow[ii][j] = p_o;
      }
    }
  } else if(dist == "uniform_bounded"){
    forn(i, 9){
      if(b[i]){///big
        int ii = id_in[i];
        int sz_b = min(sz_big(i), upper_b);
        int sz_s = min(sz_small(i), upper_b);
        int sz_o = min(sz_out(ii), 2*upper_b);
        double p_b = big/sz_b, p_s = small/sz_s, p_o = out/sz_o;
        if(sz_s == 0)  {    ///18:00 --> no more small
          p_b = (big + small)/sz_b;
        }
        fill_flow_bounded(i, p_b, p_s, sz_b, sz_s);
        fore(j, ii+1, 20){
          if(is_out(j) && sz_o) {
            flow[ii][j] = p_o;
            sz_o--;
          }
        }
      }
    }
  } else if(dist == "normal_bounded"){
      forn(i, 9){
      if(b[i]){///big
        int ii = id_in[i];
        int sz_b = min(sz_big(i), upper_b);
        int sz_s = min(sz_small(i), upper_b);
        int sz_o = min(sz_out(ii), 2*upper_b);
        double p_big = big;
        if(sz_s == 0)  {    ///18:00 --> no more small
           p_big = big + small;
        }
        fill_flow_normal_b(i, p_big, small, out, sz_b, sz_s, sz_o);
      }
    }
  }
  if(test) test_big();
}

void gen_small(string &dist, double &big, double &small, double &out, int upper_b, bool test = false){        ///tested
  if(dist == "uniform"){
    forn(i, 9){
      if(s[i]){///small
        int ii = id_in[i];
        int sz_b = sz_big(i);
        int sz_s = sz_small(i);
        int sz_o = sz_out(ii);
        double p_b = big/sz_b, p_s = small/sz_s, p_o = out/sz_o;
        if(sz_s == 0) {   /// 16:30 --> no more small
          p_b = (big + small)/sz_b;
        }
        fill_flow(i, p_b, p_s);
        fore(j, ii+1, 20)
          if(is_out(j)) flow[ii][j] = p_o;
      }
    }
  } else if(dist == "uniform_bounded"){
    forn(i, 9){
      if(s[i]){///small
        int ii = id_in[i];
        int sz_b = min(sz_big(i), upper_b);
        int sz_s = min(sz_small(i), upper_b);
        int sz_o = min(sz_out(ii), 2*upper_b);
        double p_b = big/sz_b, p_s = small/sz_s, p_o = out/sz_o;
        if(sz_s == 0) {   /// 16:30 --> no more small
          p_b = (big + small)/sz_b;
        }
        fill_flow_bounded(i, p_b, p_s, sz_b, sz_s);
        fore(j, ii+1, 20){
          if(is_out(j) && sz_o) {
            flow[ii][j] = p_o;
            sz_o--;
          }
        }
      }
    }
  } else if(dist == "normal_bounded"){
    forn(i, 9){
      if(s[i]){///small
        int ii = id_in[i];
        int sz_b = min(sz_big(i), upper_b);
        int sz_s = min(sz_small(i), upper_b);
        int sz_o = min(sz_out(ii), 2*upper_b);
        double p_big = big;
        if(sz_s == 0) {   /// 16:30 --> no more small
          p_big = big + small;
        }
        fill_flow_normal_b(i, p_big, small, out, sz_b, sz_s, sz_o);
      }
    }
  }
  if(test) test_small();
}

void gen_out(string &dist, double &big, double &small, double &out, int upper_b, bool test = false){          ///tested
  if(dist == "uniform"){
    for1(i, 17){
      if(!is_out(i)) continue;   ///big-small
      int ii = r_id[i];
      int sz_b = sz_big(ii);
      int sz_s = sz_small(ii);
      int sz_o = sz_out(i);
      double p_b = big/sz_b, p_s = small/sz_s, p_o = out/sz_o;
      if(sz_s == 0){   ///16:40 - 17:30 --> no small
        p_b = (big+small)/sz_b;
      }
      fill_flow_2(i, p_b, p_s);
      fore(j, i+1, 20)
        if(is_out(j)) flow[i][j] = p_o;
    }
  } else if(dist == "uniform_bounded"){
    for1(i, 17){
      if(!is_out(i)) continue;   ///big-small
      int ii = r_id[i];
      int sz_b = min(sz_big(ii), upper_b);
      int sz_s = min(sz_small(ii), upper_b);
      int sz_o = min(sz_out(i), 2*upper_b);
      double p_b = big/sz_b, p_s = small/sz_s, p_o = out/sz_o;
      if(sz_s == 0){   ///16:40 - 17:30 --> no small
        p_b = (big+small)/sz_b;
      }
      fill_flow_bounded_2(i, p_b, p_s, sz_b, sz_s);
      fore(j, i+1, 20){
        if(is_out(j) && sz_o){
          flow[i][j] = p_o;
          sz_o--;
        }
      }
    }
  } else if(dist == "normal_bounded"){
    for1(i, 17){
      if(!is_out(i)) continue;   ///big-small
      int ii = r_id[i];
      int sz_b = min(sz_big(ii), upper_b);
      int sz_s = min(sz_small(ii), upper_b);
      int sz_o = min(sz_out(i), 2*upper_b);
      double p_big = big;
      if(sz_s == 0){   ///16:40 - 17:30 --> no small
        p_big = big + small;
      }
      fill_flow_normal_b_2(i, p_big, small, out, sz_b, sz_s, sz_o);
    }
  }
  flow[18][19] = big + small;
  flow[18][20] = out;
  if(test) test_out();
}

void gen_flow(string &dist, double &big, double &small, double &out, int upper_b, bool test = false){         ///tested
  normalize(big, small, out, test);
  if(test) cout <<el<< "big = " << big << ",  small = " << small << ", out = " << out << el;
  gen_big(dist, big, small, out, upper_b, test);
  gen_small(dist, big, small, out, upper_b, test);
  gen_out(dist, big, small, out, upper_b, test);
  gen_prob_flow();
}


void fix(vector< pair<int, user_id> > &salidas, int cur_time, int j, norm_dist &dist_norm){   ///testing pending
  int l = (j == 0 ? 0 : ub_out[j-1]);
  int r = ub_out[j], time, exp_time;                  ///FIX FOR J-TH TIME INTERVAL
  double factor = 1.0;

  if(l + cur_time >= r)     ///Last exit exceeds upper_bound_out
    factor = double(r - l - 100)/cur_time;      ///correction factor

  forn(i, sz(salidas)){         ///user --> entries[user.id_f][user.id]
    time      = salidas[i].first;
    user_id U = salidas[i].second;
    time = int(floor(double(time) * factor));
    exp_time = time + gen_error(dist_norm);
    U_id(U).ex_t = min(max(l + time, l), r-1);
    U_id(U).exp_ex_t = max(U_id(U).ent_t + 60, min(l + exp_time, day_sz));
  }
}

void gen_exits(double mu, double sigma, bool test = false){  ///testing pending
  vector<user_id> inter[21];       ///divide users acording to arr_time_interval

  forn(i, 6){     ///for each fila
    forn(j, 21)
      inter[j].clear();

    forn(j, sz(entries[i])){
      user U = entries[i][j];
      int arr_time = U.arr_t;
      int idx = upper_bound(all(ub_in), arr_time) - ub_in.begin();///idx: intervalo de llegada
      inter[idx].push_back(user_id(U));
    }
    for1(j, 18){    ///for each arrival time-interval
      random_shuffle(all(inter[j]));    ///shuffle
      forn(k, sz(inter[j])){
        user_id U = inter[j][k];
        fore(x, j+1, 20){
          double l = prob[j][x-1]/100.0;
          double r = prob[j][x]/100.0;
          double per = double(k)/sz(inter[j]);
          if(l <= per && per <= r){                 ///assign exit_time_interval
            exits[p_id[i]][x].push_back(U);
            break;
          }
        }
      }
    }
  }
  gen_lambda_out();
  gen_dist_out();
  norm_dist dist_norm(mu, sigma);

  vector< pair<int, user_id> > salidas;
  forn(i, 4){     ///for each park-exit
    forn(j, 21){      ///for each time inteval
      int cur_time = 0;
      salidas.clear();
      forn(k, sz(exits[i][j])){              ///user -> entries[user.id_f][user.id]
        user_id U = exits[i][j][k];
        int new_exit = gen_exit(dist_out[i][j]);
        cur_time += new_exit;
        salidas.push_back({cur_time, U});
      }
      if(cur_time > 0)
        fix(salidas, cur_time, j, dist_norm);  ///make sure that users exit within time_interval
    }
  }
  if(test) test_exits();
}



///------------------ CALCULATORS ------------------///
void calc_lambda_in_real(bool test = false){        ///tested!
  forn(i, 6){
    forn(j, 21)
      l_in_real[i][j] = double(total_arr[i][j])/len_in(j);
  }
  if(test) compare_lambda_in();
}

void calc_lambda_out_real(bool test = false){       ///tested!
  forn(i, 4){
    forn(j, 21)
      l_out_real[i][j] = double(total_exits[i][j])/len_out(j);
  }
  if(test) compare_lambda_out();
}

void calc_lambda_out_exp(bool compare = false){     ///tested!
  forn(i, 4){
    forn(j, 21)
      l_out_exp[i][j] = double(total_exp_exits[i][j])/len_out(j);
  }
  if(compare) compare_l_out();
}


#endif // GENERATOR_H
