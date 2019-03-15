#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstddef>

class network {
  std::vector<std::vector<int>> links;

  public:
    enum class colour { white = 0, grey, black, green, red };
    network() noexcept {}
    network(int n) noexcept : links(static_cast<size_t>(n)) // reserve space for needed links
    {}

    network(ssize_t n) noexcept : network{static_cast<int>(n)} {}
    network(size_t n) noexcept : network{static_cast<int>(n)} {}
    ~network() = default;

    bool add_link(const int u, const int v) noexcept
    {
      if (u >= n_nodes() || v >= n_nodes()) return false;
      if (u == v || has_link(u, v)) return true;
      links[u].push_back(v);
      links[v].push_back(u);
      return true;
    }

    inline bool rem_link(const int u, const int v) noexcept
    {
      if (u >= n_nodes() || v >= n_nodes() || u == v) return false;
      auto it1 = std::find(links[u].cbegin(), links[u].cend(), v);
      auto it2 = std::find(links[v].cbegin(), links[v].cend(), u);
      if (it1 != links[u].end()) links[u].erase(it1);
      if (it2 != links[v].end()) links[v].erase(it2);
      return true;
    }

    inline bool has_link(const int u, const int v) const noexcept
    {
      return (u < n_nodes() && u >= 0 && v < n_nodes() && v >= 0)
          && ( u == v || std::find(links[u].cbegin(), links[u].cend(), v) != links[u].end());
    }

    inline const std::vector<int> &neighbours(const int u) const noexcept
    {
      if (u >= n_nodes() || u < 0) std::vector<int>();
      return links[u];
    }

    inline void add_node() noexcept { links.emplace_back(); }
    inline int n_nodes() const noexcept { return links.size(); }
};

std::ostream & operator<<(std::ostream &os, const network &n) noexcept;

network create_network(std::istream &in) noexcept;

inline network create_network(const std::string &filename) noexcept;

