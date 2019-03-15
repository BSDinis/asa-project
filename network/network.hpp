#pragma once

#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstddef>

class network {
  std::vector<std::set<int>> links;

  public:
    enum class colour { white = 0, grey, black, green, red };
    network() noexcept : network{32} {}
    network(int n) noexcept : links(static_cast<size_t>(n)) // reserve space for needed links
    {}

    network(ssize_t n) noexcept : network{static_cast<int>(n)} {}
    network(size_t n) noexcept : network{static_cast<int>(n)} {}
    ~network() = default;

    bool add_link(const int u, const int v) noexcept
    {
      if (u >= n_nodes() || v >= n_nodes()) return false;
      if (u == v) return true;
      return links[u].insert(v).second && links[v].insert(u).second;
    }

    inline bool rem_link(const int u, const int v) noexcept
    {
      if (u >= n_nodes() || v >= n_nodes() || u == v) return false;
      return links[u].erase(v) == 1 && links[v].erase(u) == 1;;
    }

    inline bool has_link(const int u, const int v) const noexcept
    {
      return (u < n_nodes() && u >= 0 && v < n_nodes() && v >= 0)
          && ( u == v || links[u].find(v) != links[u].end());
    }

    inline const std::set<int> &neighbours(const int u) const noexcept
    {
      if (u >= n_nodes() || u < 0) std::set<int>();
      return links[u];
    }

    inline void add_node() noexcept { links.emplace_back(); }
    inline int n_nodes() const noexcept { return links.size(); }
};

std::ostream & operator<<(std::ostream &os, const network &n) noexcept;

network create_network(std::istream &in) noexcept;

inline network create_network(const std::string &filename) noexcept;

