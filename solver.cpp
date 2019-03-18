#include "network.hpp"
#include "net_algs.hpp"
#include <iostream>
#include <vector>

int main()
{
  const auto &net = create_network(std::cin);
#ifdef DEBUG
  std::clog << net;
#endif

  int n_articulation_pts=0;
  int max = 0;

  const auto ids = dfs_tarjan(net, n_articulation_pts, max);
  std::cout << ids.size();
#ifdef DEBUG
  std::clog << " [number of subnets]";
#endif
  std::cout << '\n';

  for (ssize_t i = ids.size() - 1; i >= 0; i--) {
    const auto &id = ids[i];
    std::cout << id+1; // get it normalized
    if (i != 0) std::cout << ' ';
  }

#ifdef DEBUG
  std::clog << " [sub net ids]";
#endif
  std::cout << '\n';

  std::cout << n_articulation_pts;
#ifdef DEBUG
  std::clog << " [number articulation_pts]";
#endif
  std::cout << '\n';

  std::cout << max;
#ifdef DEBUG
  std::clog << " [rem sub net]";
#endif
  std::cout << "\n";

  return 0;
}
