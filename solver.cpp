#include "network.hpp"
#include "net_algs.hpp"
#include <iostream>
#include <vector>

void first_part(const network & net, std::vector<int> &articulation_pts);
void second_part(const network & net, const std::vector<int> &articulation_pts);
int main()
{
  const auto &net = create_network(std::cin);
  std::vector<int> articulation_pts;
  first_part(net, articulation_pts); // compute articulation pts
  std::cout << dfs(net, articulation_pts) << '\n'; // remove articulation pts and calc max subnet
  return 0;
}

// hack: this forces the stack size to be controlled (clears the stack before the seconde dfs)
void first_part(const network & net, std::vector<int> &articulation_pts)
{
  const auto ids = dfs_tarjan(net, articulation_pts);

  std::cout << ids.size() << '\n';
  for (ssize_t i = ids.size() - 1; i >= 0; i--) {
    const auto &id = ids[i];
    std::cout << id+1; // get it normalized
    if (i != 0) std::cout << ' ';
  }

  std::cout << '\n' << articulation_pts.size() << '\n';
}
