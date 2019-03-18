#pragma once
#include "network.hpp"

std::vector<std::vector<int>> dfs(const network &net) noexcept ;

std::vector<int> dfs_tarjan(
    const network &net,
    std::vector<int> &articulation_pts
    ) noexcept ;

int dfs(
    const network &net,
    const std::vector<int> &removed_pts
    ) noexcept ;
