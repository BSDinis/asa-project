#include "network.hpp"
#include "net_algs.hpp"
#include <iostream>
#include <vector>

void first_part(const network & net, std::vector<int> &articulation_pts);
void second_part(const network & net, const std::vector<int> &articulation_pts);
int main()
{
  const auto &net = create_network(std::cin);
#ifdef DEBUG
  std::cout << net;
#endif

  std::vector<int> articulation_pts;

  first_part(net, articulation_pts);
  second_part(net, articulation_pts);

  return 0;
}

void second_part(const network & net, const std::vector<int> &articulation_pts)
{
  std::cout << dfs(net, articulation_pts);
#ifdef DEBUG
  std::cout << " [rem sub net]";
#endif
  std::cout << "\n";
}

void first_part(const network & net, std::vector<int> &articulation_pts)
{
  const auto ids = dfs_tarjan(net, articulation_pts);
  std::cout << ids.size();
#ifdef DEBUG
  std::cout << " [number of subnets]";
#endif
  std::cout << '\n';

  for (ssize_t i = ids.size() - 1; i >= 0; i--) {
    const auto &id = ids[i];
    std::cout << id+1; // get it normalized
    if (i != 0) std::cout << ' ';
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
}
