#!/usr/bin/python3

import random
import sys

n = random.randrange(1<<10, 1<<15);
m = random.randrange(n // 4, n)

connections = list();

print(n)
print(m)
i = 0;
while i < m:
    l = list(range(n))
    u = random.choice(l)
    del(l[u]);
    v = random.choice(l)

    if (u > v):
        pair = (v, u)
    else:
        pair = (u, v)

    if pair not in connections:
        print(f"{u+1} {v+1}")
        connections.append(pair)
        i+=1
