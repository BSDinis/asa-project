#include "network.hpp"
#include "net_algs.hpp"
#include <iostream>
#include <vector>
#include <set>

int main()
{
  std::ios_base::sync_with_stdio(false);
  network net = create_network(std::cin);
#ifdef DEBUG
  std::cout << net;
#endif

  std::vector<int> articulation_pts;

  const auto forest = dfs_tarjan(net, articulation_pts);
  std::cout << forest.size();
#ifdef DEBUG
  std::cout << " [number of subnets]";
#endif
  std::cout << '\n';

  std::set<int> max_subnet_ids;
  for (const auto &tree : forest)
    max_subnet_ids.insert(*std::max_element(tree.begin(), tree.end()) + 1);

  size_t i = 1;
  for (const auto &id : max_subnet_ids) {
    std::cout << id;
    if (i++ < max_subnet_ids.size()) std::cout << ' ';
  }

#ifdef DEBUG
  std::cout << " [sub net ids]";
#endif
  std::cout << '\n';

  std::cout << articulation_pts.size();
#ifdef DEBUG
  std::cout << " [number articulation_pts]";
#endif
  std::cout << '\n';

  int max_n_routers_in_rem_sub_net = 0;

  const auto rem_forest = dfs(net, articulation_pts);
  for (const auto &tree : rem_forest)
  	if ( (int)tree.size() > max_n_routers_in_rem_sub_net )
  		max_n_routers_in_rem_sub_net = tree.size();

  std::cout << max_n_routers_in_rem_sub_net;
#ifdef DEBUG
  std::cout << " [rem sub net]";
#endif
  std::cout << "\n";
  return 0;
}

