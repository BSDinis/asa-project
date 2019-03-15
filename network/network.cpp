#include "network.hpp"
std::ostream & operator<<(std::ostream &os, const network &n) noexcept
{
  const ssize_t nnodes = n.n_nodes();
  ssize_t links = 0;
  ssize_t lineno = 1;
  for (ssize_t v = 1; v < nnodes; v++) {
    for (ssize_t u = 0; u < v; u++) {
      if (n.has_link(u, v)) {
        os << "[" << lineno++ << "] : (" << u+1 << ") <-=-> (" << v+1 << ")\n";
        links++;
      }
    }
  }

  return os << nnodes << " nodes\n" << links/2 << " links\n";
}

network create_network(std::istream &in) noexcept
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

  network net{n};
  for (ssize_t i = 0; i < m; i++) {
    int u, v;
    if (! (in >> u >> v) ) {
      std::cerr << "create_router: line [" << i + 1 << "]: failed to read two nodes\n";
      exit(EXIT_FAILURE);
    }

    u--; v--;
    if (u < 0) {
      std::cerr << "create_router: line [" << i + 1 << "]: cannot process non-positive value " << u + 1 << "\n";
      exit(EXIT_FAILURE);
    }
    else if (u >= n) {
      std::cerr << "create_router: line [" << i + 1 << "]: overflow " << u + 1 << "nodes should not be greater than " << n << "\n";
      exit(EXIT_FAILURE);
    }
    if (v < 0) {
      std::cerr << "create_router: line [" << i + 1 << "]: cannot process non-positive value " << v + 1 << "\n";
      exit(EXIT_FAILURE);
    }
    else if (v >= n) {
      std::cerr << "create_router: line [" << i + 1 << "]: overflow " << v + 1 << "nodes should not be greater than " << n << "\n";
      exit(EXIT_FAILURE);
    }

    if (!net.add_link(u, v)) {
      std::cerr << "create_router: line [" << i + 1 << "]: failed to create link from " << u + 1 << "to " << v + 1 <<"\n";
      std::cerr << "n_vertices: " << net.n_nodes() << '\n';
      std::cerr << "u: " << u + 1<< '\n';
      std::cerr << "v: " << v + 1<< '\n';
      exit(EXIT_FAILURE);
    }
  }

  return net;
}

inline network create_network(const std::string &filename) noexcept
{
  std::ifstream in{filename};
  return create_network(in);
}
