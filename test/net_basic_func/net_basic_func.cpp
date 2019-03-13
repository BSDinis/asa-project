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


#include "network.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

const int n_nodes = 10;
const int n_links_to_add = 20;
const int n_links_to_rem = 4;

// add vertices
void test_1(network::network &g);

// add edges
void test_2(network::network &g);

// return vertices
void test_3(network::network &g);

// remove edges
void test_4(network::network &g);


int main()
{
  network::network n;
  std::srand(std::time(NULL));

  test_1(n);
  test_2(n);
  std::cout << n;
  test_3(n);
  std::cout << n;
  return 0;
}


void test_1(network::network &g)
{
  std::cout << g;
  for (int i = 0; i < n_nodes; i++)
    g.add_node();
}

void test_2(network::network &g)
{
  std::cout << g;
  for (int i = 0; i < n_links_to_add; i++)
    g.add_link(std::rand() % n_nodes, std::rand() % n_nodes);
}


void test_3(network::network &g)
{
  std::cout << g;
  for (int i = 0; i < n_links_to_rem; i++)
    g.rem_link(std::rand() % n_nodes, std::rand() % n_nodes);
}

