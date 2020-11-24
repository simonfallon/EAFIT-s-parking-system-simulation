#include "generator.h"

/// ----------------- SIMULATION METHODS ------------------ ///

void prepare_simulation(){
  forn(i, 6)
    F[i] = fila(i, max_fila[i]);

  forn(i, 4)
    P[i] = park(i, max_park[i]);
}

int best_fila(user Us, double prob_guay){     ///app-users
  iii best = {inf, inf, inf};     ///sz_fila, dist, idx
  forn(i, 6){
     if(i == Us.id_f) continue;
     if(!Us.emp && (i==0 || i==3)) continue;
     if(F[i].siz == F[i].max_cap) continue;
     best = min(best, {F[i].siz, d[Us.id_f][i], i});
   }
   int a, b, c;    tie(a, b, c) = best;
   return c;
}

int next_fila(user Us, double prob_guay){     ///others
  int id_fila = Us.id_f;
  if(Us.emp){   ///EMPLEADO

    if(id_fila != 4){   /// NO NORTH
      return (id_fila + 1)%6;
    }else{              ///    NORTH
      double r = get_rand();
      if(r <= prob_guay)
        return 5;     ///GUAYABOS
      else
        return 0;     ///EMP-VEGAS
    }

  }else{              ///NO-EMPLEADO

    if(id_fila == 1){         ///SOUTH-VEGAS
      return 2;       ///SOUTH-REGIONAL
    }
    else if(id_fila == 2){  ///SOUTH-REGIONAL
      return 4;       ///NORTH-REGIONAL
    }
    else if(id_fila == 5){ ///GUAYABOS
      return 1;       ///SOUTH-VEGAS
    }
    else{                  ///NORTH
      double r = get_rand();
      if(r <= prob_guay)
        return 5;     ///GUAYABOS
      else
        return 1;     ///SOUTH-VEGAS
    }
  }
}

inline void entry_fila(user_id U, int i){
  U_id(U).arr_t_real = cur_t;
  U_id(U).id_f_real = i;
  F[i].add_user(U);
}

inline void exit_system(user_id U){
  lost[U.idx_f]++;
  U_id(U).arr_t_real = -1;
}

inline void entry_aux(int i){
  user_id U = F[i].entry_user();
  P[p_id[i]].add_user(U);
  U_id(U).ent_t = cur_t;
}

inline void exit_aux(int i){
  user_id U = P[i].exit_user();
  U_id(U).ex_t_real = cur_t;
}

inline void transition_from_to(user_id U, int i, int next_f){
  U_id(U).tran_t += (d[i][next_f] + 15);
  U_id(U).num_tran++;
  F[next_f].next.push_back(U);
}

void add_or_transition(user_id U, int i, bool transition, double prob_guay, int max_tran){
  if(F[i].is_full()){  ///FILA LLENA
    if(transition && U_id(U).num_tran < max_tran){ ///-> OTRA FILA
      int next_f;
      if(U_id(U).app)        ///USA LA APP
        next_f = best_fila(U_id(U), prob_guay);      // d(1); d(next_f);
      else                   ///
        next_f = next_fila(U_id(U), prob_guay);      // d(2); d(next_f);

      if(next_f == inf)      ///SYSTEMA LLENO
        exit_system(U);
      else                   ///TRANSICIÓN A OTRA FILA
        transition_from_to(U, i, next_f);

    } else{               ///NUM_T = MAX_TRAN
      exit_system(U);
    }
  } else{              ///FILA DISPONIBLE
    entry_fila(U, i);
  }
}

void extract_data(){
  forn(i, 6){
    int sz_i = sz(entries[i]);

    trans_to[i].assign(sz_i, -1);
    t_in_line[i].assign(sz_i, -1);
    t_in_park[i].assign(sz_i, -1);
    t_in_sys[i].assign(sz_i, -1);

    forn(j, sz_i){
      user U = entries[i][j];
      if(U.tran_t > 0)
        trans_to[i][j] = U.id_f_real;

      if(U.arr_t_real != -1){
        t_in_line[i][j] = U.ent_t - U.arr_t_real;
        t_in_park[i][j] = U.ex_t_real - U.ent_t;
        t_in_sys[i][j]  = U.tran_t + (t_in_line[i][j] + t_in_park[i][j]);
      }
    }
  }
}

void print_results(bool transition){
  freopen("time.txt", "w", stdout);
  forn(i, day_sz){
    cout << to_time_seg(i, 1) << el;
  }

  freopen("filas.txt", "w", stdout);
  forn(j, day_sz){
    forn(i, 6){
      if(i) cout << ",";
      cout << occ_f[i][j];
    }
    cout << el;
  }

  freopen("parks.txt", "w", stdout);
  forn(j, day_sz){
    forn(i, 4){
      if(i) cout << ",";
      cout << occ_p[i][j];
    }
    cout << el;
  }

  freopen("user_labels.txt", "w", stdout);
  cout<<"id_fila "<<"id_fila_real "<<"arr_time "<<"arr_time_real ";
  cout<<"entry_time "<<"exit_time "<<"exp_exit_time ";
  cout<<"t_in_line "<<"t_in_park " <<"t_in_sys " <<el;

  freopen("users.txt", "w", stdout);
  forn(i, 6){
    int sz_i = sz(entries[i]);
    forn(j, sz_i){
      user u = entries[i][j];
      cout<< u.id_f<<","<< u.id_f_real<<","<< u.arr_t<<","<< u.arr_t_real<<",";
      cout<< u.ent_t<<","<< u.ex_t<<","<< u.exp_ex_t<<",";
      cout<< t_in_line[i][j]<<","<< t_in_park[i][j]<<","<< t_in_sys[i][j]<<el;
    }
  }

  if(transition){
    freopen("tran.txt", "w", stdout);
    forn(i, 6){
      int sz_i = sz(entries[i]);
      forn(j, sz_i){
        cout << i+1 <<","<< entries[i][j].app << ","<<entries[i][j].emp<<",";
        cout << entries[i][j].num_tran << ","<< entries[i][j].tran_t <<",";
        cout << trans_to[i][j] << el;
      }
    }
  }

  freopen("lost.txt", "w", stdout);
  forn(i, 6){
    if(i) cout << ",";
    cout << sz(entries[i]);
  }
  cout << el;
  forn(i, 6){
    if(i) cout << ",";
    cout << lost[i];
  }
}

void simulate_day(double prob_guay, int max_tran, bool transition){
  prepare_simulation();
  vector<int> pt(6, 0);   ///POINTER TO "NEXT" ARRIVING USER (ENTRIES)
  forn(z, day_sz){
    cur_t = z;            ///TIME

    forn(i, 6){           ///FOR EACH QUEUE
      int sz_i = sz(entries[i]);
      F[i].update_time();

      if(pt[i] < sz_i && entries[i][pt[i]].arr_t <= cur_t){ ///ENTRIES -> NEXT
        user U = entries[i][pt[i]];
        F[i].next.push_back(user_id(U));
        pt[i]++;
      }

      F[i].sort_next();

      if(F[i].is_next()){    ///NEXT -> FILA/TRANSITION
        user_id U = F[i].first_next();
        add_or_transition(U, i, transition, prob_guay, max_tran);
      }

      if(F[i].can_entry() && P[p_id[i]].can_entry()){  ///ENTRY USER IN QUEUE
        entry_aux(i);
      }
      occ_f[i][cur_t] = F[i].siz;
    }

    forn(i, 4){                     ///FOR EACH PARK
      P[i].update_time();
      if(P[i].can_exit()){
        exit_aux(i);
      }
      occ_p[i][cur_t] = P[i].siz;
    }
  }
  extract_data();
  print_results(transition);
}

int main(){
  cout<< setprecision(3)<< fixed;
  string arr_dist, flow_dist; int max_tran, upper_b;
  double big, small, out, mu, sigma, p_app, p_guay;
  cin >> arr_dist >> flow_dist >> big >> small >> out>> upper_b;
  cin >> mu >> sigma >> p_app >> p_guay >> max_tran;
  bool test = true;
  pre(test);
  gen_arrivals(arr_dist, big, small, out, test);
  gen_entries(test, p_app);
  gen_flow(flow_dist, big, small, out, upper_b, test);
  calc_lambda_in_real(test);
  gen_exits(mu, sigma, test);
  calc_lambda_out_real(test);
  calc_lambda_out_exp(test);
  bool transition = true;
  simulate_day(p_guay, max_tran, transition);
}
