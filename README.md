---
title: graphlib
---

Copyright (C) Afonso Ribeiro & Baltasar Dinis

## Purpose

To implement a _general purpose_ graph library in `C++`, with focus on efficiency.
We also aim to provide flexibility to the user, supporting different representations.

## Representations

To begin with we will support two implementations

1. Adjacency matrix
2. Adjacency list

Also, there will be differences in implementing

1. Non-directional graphs
2. Directional graphs
3. Non-directional multigraphs
4. Directional multigraphs

### Nodes

The nodes will hold a value, and also contain some private data.

+ Colour, to help implement algorithms such as DFS
+ Listing of in connections and out connections


## Algorithms

To begin with, lets aim for these:

+ Tarry
+ Tremaux
+ BFS
+ DFS
+ Djikstra
+ Kruskal
+ Ford-Fulkerson

+ Finding SCC
+ Finding eulerian paths
+ Finding hamiltonian cicles

+ Others?
