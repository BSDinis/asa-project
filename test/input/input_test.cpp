#include "network.hpp"
#include <iostream>


int main()
{
  network net = create_network(std::cin);
  std::cout << net;
  return 0;
}

