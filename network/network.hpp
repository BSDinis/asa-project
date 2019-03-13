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
  inline ssize_t link_pos(const int u, const int v) const
  {
    if (u < v) return v * (v - 1) / 2 + u;
    return u * (u - 1) / 2 + v;
  }

  public:
    network() : network{32} {}
    network(int n) :
      nlinks{0},  // no links
      nnodes{0},  // n nodes
      links(static_cast<size_t>(n * (n - 1) / 2), false) // reserve space for needed links
    {}

    network(ssize_t n) : network{static_cast<int>(n)} {}
    network(size_t n) : network{static_cast<int>(n)} {}
    ~network() = default;

    bool add_link(const int u, const int v);
    bool rem_link(const int u, const int v);

    inline bool has_link(const int u, const int v) const
    {
      return u < nnodes && v < nnodes && u != v && links[link_pos(u, v)];
    }

    int add_node();

    inline int n_nodes() const { return nnodes; }
    inline int n_links() const { return nlinks; }
};

std::ostream & operator<<(std::ostream &os, const network &n);
network create_network(const std::string &filename);
network create_network(std::istream &in);
std::vector<int> neighbour_routers(const network &net, const int node);
