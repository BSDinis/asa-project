/**
 * basic_func.cpp
 *
 * test if basic functionality is met:
 *   - create & destroy
 *   - add and remove edges
 *   - add vertices
 *   - return vertices
 *   - print
 */


#include "graph.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

const int n_vertices = 10;
const int n_edges_to_add = 20;
const int n_biedges_to_add = 20;
const int n_edges_to_rem = 4;
const int n_biedges_to_rem = 6;

// add vertices
template <typename T>
void test_1(graph::graph<T> &g);

// add edges
template <typename T>
void test_2(graph::graph<T> &g);

// return vertices
template <typename T>
void test_3(graph::graph<T> &g);

// remove edges
template <typename T>
void test_4(graph::graph<T> &g);


int main()
{
  graph::graph<int> g;
  std::srand(std::time(NULL));

  test_1(g);
  test_2(g);
  test_3(g);
  test_4(g);
  std::cout << g;
  return 0;
}


template <typename T>
void test_1(graph::graph<T> &g)
{
  std::cout << g;
  for (int i = 0; i < n_vertices; i++)
    g.add_vertex(std::rand());
}

template <typename T>
void test_2(graph::graph<T> &g)
{
  std::cout << g;
  for (int i = 0; i < n_edges_to_add; i++)
    g.add_edge(std::rand() % n_vertices, std::rand() % n_vertices);

  for (int i = 0; i < n_biedges_to_add; i++)
    g.add_biedge(std::rand() % n_vertices, std::rand() % n_vertices);
}

template <typename T>
void test_3(graph::graph<T> &g)
{
  std::cout << g;
  for (int i = 0; i < n_vertices; i++)
    std::cout << i << ": " << g.get_vertex(i) << std::endl;
}

template <typename T>
void test_4(graph::graph<T> &g)
{
  std::cout << g;
  for (int i = 0; i < n_edges_to_rem; i++)
    g.rem_edge(std::rand() % n_vertices, std::rand() % n_vertices);

  for (int i = 0; i < n_biedges_to_rem; i++)
    g.rem_biedge(std::rand() % n_vertices, std::rand() % n_vertices);
}

