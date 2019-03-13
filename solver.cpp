#include "network.hpp"
#include "net_algs.hpp"
#include <iostream>
#include <vector>


int main()
{
  network net = create_network(std::cin);
  std::cout << net;

  std::vector<int> articulation_pts;

  const auto forest = dfs_tarjan(net, articulation_pts);
  std::cout << "number of subnets : " << forest.size() << "\nsub net ids : ";
  for (const auto &tree : forest)
    std::cout << *std::max_element(tree.begin(), tree.end()) + 1 << " "; // not ordered
  std::cout << "\nnumber articulation_pts : " << articulation_pts.size() << "\nrem sub net : ";

  int max_n_routers_in_rem_sub_net = 0;
  const auto rem_forest = dfs(net, articulation_pts);
  for (const auto &tree : rem_forest)
  	if ( (int)tree.size() > max_n_routers_in_rem_sub_net )
  		max_n_routers_in_rem_sub_net = tree.size();
  std::cout << max_n_routers_in_rem_sub_net << "\n";
  return 0;
}

