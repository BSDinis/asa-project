#pragma once
#include "network.hpp"
std::vector<int> neighbour_routers(
    const network &net, const int node
    );

std::vector<std::vector<int>> dfs(const network &net);

std::vector<std::vector<int>> dfs(
    const network &net,
    const ssize_t root,
    std::vector<int> &articulation_pts
    );

std::vector<int> neighbour_routers(
    const network &net, const int node
    );
