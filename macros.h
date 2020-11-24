#ifndef MACROS_H
#define MACROS_H

#include <bits/stdc++.h>
#define fi first
#define se second
#define forn(i, n) for(int i=0; i< (int)n; ++i)
#define for1(i, n) for(int i=1; i<= (int)n; ++i)
#define fore(i, l, r) for(int i=(int)l; i<=(int)r; i++)
#define el '\n'
#define d(x) cout<< #x<< " " << x<<el
#define sz(v) ((int)v.size())
#define all(v) v.begin(), v.end()
#define U_id(u) entries[u.idx_f][u.idx]


using namespace std;

typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef exponential_distribution<double> exp_dist;
typedef normal_distribution<double> norm_dist;

#endif // MACROS_H
