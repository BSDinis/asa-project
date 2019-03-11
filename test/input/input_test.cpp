#include "graph.hpp"
#include "network_factory.hpp"

#include <iostream>

int main()
{
  using namespace network;
  network_t n = create_network(std::cin);
  std::cout << n;
}
