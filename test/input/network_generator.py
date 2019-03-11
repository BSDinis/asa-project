#!/usr/bin/python3

import random
import sys

mmin = 8
mmax = 16

n = random.randrange(mmin, mmax);
Mmax = (n * (n - 1)) // 6;
Mmin = (n * (n - 1)) // 12;
m = random.randrange(Mmin, Mmax)

connections = list();

print(n)
print(m)
i = 0;
print(n, file=sys.stderr)
print(m, file=sys.stderr)
while i < m:
    l = list(range(n))
    u = random.choice(l)
    del(l[u]);
    v = random.choice(l)
    if (u > v):
        u, v = u, v;

    pair = (u, v)
    if pair not in connections:
        print(f"{u+1} {v+1}")
        connections.append(pair)
        i+=1
