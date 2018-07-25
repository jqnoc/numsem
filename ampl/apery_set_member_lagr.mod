param n; # number of generators of S
set N := 1..n;
param a {N}; # generators of S
param s; # integer s for Ap(S,s)
param i; # index of w_i \in Ap(S,s)
param lambda;
param rest;
var X {N} integer, >= 0;
var K integer;

minimize T:
    sum {j in N} a[j]*X[j] + lambda*((sum {j in N} a[j]*X[j] - i - s*K)^2);
