#include "network.hpp"
#include "net_algs.hpp"
#include <iostream>
#include <vector>


int main()
{
  network net = create_network(std::cin);
  std::cout << net;

  const auto forest = dfs(net);
  std::cout << "number of subnets : " << forest.size() << "\nsub net ids : ";
  for (const auto &tree : forest)
    std::cout << *std::max_element(tree.begin(), tree.end()) + 1 << " ";
  std::cout << std::endl;

  return 0;
}

