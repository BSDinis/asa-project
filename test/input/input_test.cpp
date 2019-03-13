#include "network.hpp"
#include <iostream>

int main()
{
  network n = create_network(std::cin);
  std::cout << n;
}
