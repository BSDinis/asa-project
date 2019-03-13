#pragma once

std::vector<int> neighbour_routers(
    const network &net, const int node
    );

std::vector<std::vector<int>> dfs(const network &net);

std::vector<int> neighbour_routers(
    const network &net, const int node
    );
