/**
 * router_factory.cpp
 *
 * implementation
 */

#include "network_factory.hpp"

namespace network
{
  using namespace graph;
  network_t create_network(const std::string &filename)
  {
    std::ifstream in{filename};
    return create_network(in);
  }

  network_t create_network(std::istream &in)
  {
    ssize_t n, m;
    if (!(in >> n)) {
      std::cerr << "create_router: failed to get n\n";
      exit(EXIT_FAILURE);
    }
    if (!(in >> m)) {
      std::cerr << "create_router: failed to get m\n";
      exit(EXIT_FAILURE);
    }

    network_t net{n};
    for (ssize_t i = 0; i < m; i++) {
      int u, v;
      if (! (in >> u >> v) ) {
        std::cerr << "create_router: line [" << i + 1 << "]: failed to read two nodes\n";
        exit(EXIT_FAILURE);
      }

      u--; v--;
      if (u < 0 || u >= n) {
        std::cerr << "create_router: line [" << i + 1 << "]: cannot process non-positive value " << u + 1 << "\n";
        exit(EXIT_FAILURE);
      }
      else if (v < 0 || v >= n) {
        std::cerr << "create_router: line [" << i + 1 << "]: cannot process non-positive value " << v + 1 << "\n";
        exit(EXIT_FAILURE);
      }

      while (u >= net.n_vertices()) {
        net.add_vertex(0);
      }
      while (v >= net.n_vertices()) {
        net.add_vertex(0);
      }

      if (!net.add_biedge(u, v)) {
        std::cerr << "create_router: line [" << i + 1 << "]: failed to create bidirectional edge from " << u + 1 << "to " << v + 1 <<"\n";
        std::cerr << "n_vertices: " << net.n_vertices() << '\n';
        std::cerr << "u: " << u << '\n';
        std::cerr << "v: " << v << '\n';
        exit(EXIT_FAILURE);
      }
    }

    return net;
  }
}
