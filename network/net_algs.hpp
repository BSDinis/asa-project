#pragma once
#include "network.hpp"
std::vector<int> neighbour_routers(
    const network &net, const int node
    );

std::vector<std::vector<int>> dfs(const network &net);

std::vector<std::vector<int>> dfs_tarjan(
    const network &net,
    std::vector<int> &articulation_pts
    );

std::vector<std::vector<int>> dfs(
    const network &net,
    std::vector<int> &removed_pts
    );

std::vector<int> neighbour_routers(
    const network &net, const int node
    );
