#pragma once
#include "network.hpp"

std::vector<std::vector<int>> dfs(const network &net) noexcept ;

std::vector<std::vector<int>> dfs_tarjan(
    const network &net,
    std::vector<int> &articulation_pts
    ) noexcept ;

std::vector<std::vector<int>> dfs(
    const network &net,
    std::vector<int> &removed_pts
    ) noexcept ;

std::vector<int> neighbour_routers(
    const network &net, const int node
    ) noexcept ;
