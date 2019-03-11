/**
 * router_factory.cpp
 *
 * implementation
 */

#include "router_factory.hpp"

namespace graph
{
  graph<router_id> create_network(const std::string &filename)
  {
    ifstream in{filename};
    return create_router(in);
  }

  graph<router_id> create_router(std::istream &in)
  {
    ssize_t n, m;
    if (! (in >> n >> m) ) {
      std::cerr << "create_router: failed to get n and m\n";
      exit(EXIT_FAILURE);
    }

    graph<router_id> network{n};
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

      if (u >= network.n_vertices()) {
        network.add_vertex(0);
      }
      if (v >= network.n_vertices()) {
        network.add_vertex(0);
      }

      if (!network.add_biedge(u, v)) {
        std::cerr << "create_router: line [" << i + 1 << "]: failed to create bidirectional edge from " << u + 1 << "to " << v + 1 <<"\n";
        exit(EXIT_FAILURE);
      }
    }

    return network;
  }
}
