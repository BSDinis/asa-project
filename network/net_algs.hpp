#pragma once
#include "network.hpp"

std::vector<int> dfs_tarjan(
    const network &net,
    int &n_articulation_pts,
    int &max ) noexcept ;
