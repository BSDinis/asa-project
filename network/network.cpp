#include "network.hpp"

bool network::add_link(const int u, const int v)
{
  if (u > nnodes || v > nnodes || u == v) return false;
  if (!has_link(u, v)) nlinks++;
  return links[link_pos(u, v)] = true;
}

bool network::rem_link(const int u, const int v)
{
  if (u > nnodes || v > nnodes || u == v) return false;
  if (has_link(u, v)) nlinks--;
  links[link_pos(u, v)] = false;
  return true;
}

int network::add_node()
{
  nnodes++;
  links.reserve(nnodes * (nnodes - 1) / 2);
  std::fill(links.begin() + link_pos(nnodes - 1, 0), links.end(), false);
  return nnodes - 1;
}

std::ostream & operator<<(std::ostream &os, const network &n)
{
  const ssize_t nnodes = n.n_nodes();
  ssize_t lineno = 1;
  for (ssize_t u = 1; u < nnodes; u++)
    for (ssize_t v = 0; v < u; v++)
      if (n.has_link(u, v))
        os << "[" << lineno++ << "] : (" << u << ") <-=-> (" << v << ")\n";

  return os << nnodes << " nodes\n" << n.n_links() << " links\n";
}

network create_network(const std::string &filename)
{
  std::ifstream in{filename};
  return create_network(in);
}

network create_network(std::istream &in)
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

    while (u >= net.n_nodes()) {
      net.add_node();
    }
    while (v >= net.n_nodes()) {
      net.add_node();
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

std::vector<int> neighbour_routers(const network &net, const int node)
{
  std::vector<int> res;
  ssize_t nnodes = net.n_nodes();
  if (node < 0 || node >= nnodes) return res;
  for (int i = 0; i < nnodes; i++)
    if (net.has_link(i, node))
      res.push_back(i);

  return res;
}
