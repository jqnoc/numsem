param n; # number of generators of S
set N := 1..n;
param a {N}; # generators of S
param s; # integer s for Ap(S,s)
param i; # index of w_i \in Ap(S,s)
var X {N} integer, >= 0;
var K integer;

minimize T:
    sum {j in N} a[j]*X[j];

subject to C:
    sum {j in N} a[j]*X[j] = i + s*K;
