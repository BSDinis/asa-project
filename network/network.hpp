#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstddef>

class network {
  ssize_t nlinks;
  ssize_t nnodes;
  std::vector<bool> links;

  // position of a link in the truncated adj matrix
  inline ssize_t link_pos(const int u, const int v) const noexcept
  {
    if (u < v) return v * (v - 1) / 2 + u;
    return u * (u - 1) / 2 + v;
  }

  public:
    enum class colour { white = 0, grey, black, green, red };
    network() noexcept : network{32} {}
    network(int n) noexcept :
      nlinks{0},  // no links
      nnodes{n},  // n nodes
      links(static_cast<size_t>(n * (n - 1) / 2), false) // reserve space for needed links
    {}

    network(ssize_t n) noexcept : network{static_cast<int>(n)} {}
    network(size_t n) noexcept : network{static_cast<int>(n)} {}
    ~network() = default;

    bool add_link(const int u, const int v) noexcept;
    bool rem_link(const int u, const int v) noexcept;

    inline bool has_link(const int u, const int v) const noexcept
    {
      return u < nnodes && v < nnodes && u != v && links[link_pos(u, v)];
    }

    int add_node() noexcept;
    inline int n_nodes() const noexcept { return nnodes; }
    inline int n_links() const noexcept { return nlinks; }
};

std::ostream & operator<<(std::ostream &os, const network &n) noexcept;
network create_network(const std::string &filename) noexcept;
network create_network(std::istream &in) noexcept;

