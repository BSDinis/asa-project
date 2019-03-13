#include "network.hpp"
#include "net_algs.hpp"

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


static void dfs_visit(const network &net,
    std::vector<network::colour> &node_colour,
    std::vector<int> &tree,
    const int init_node);

std::vector<std::vector<int>> dfs(const network &net)
{
  using colour=network::colour;
  using std::vector;
  vector<vector<int>> forest;
  vector<colour> node_colour(net.n_nodes(), colour::white);

  ssize_t nnodes = net.n_nodes();
  for (int i = 0; i < nnodes; i++) {
    if (node_colour[i] != colour::white) continue;
    vector<int> tree = {i};
    dfs_visit(net, node_colour, tree, i);
    forest.push_back(tree);
  }

  return forest;
}

static void dfs_visit(const network &net,
    std::vector<network::colour> &node_colour,
    std::vector<int> &tree,
    const int init_node)
{
  using colour=network::colour;
  using std::vector;
  node_colour[init_node] = colour::grey;
  std::vector<int> adjacents = neighbour_routers(net, init_node);
  for (int adj_id : adjacents) {
    if ( node_colour[adj_id] == colour::white ) {
      tree.push_back(adj_id);
      dfs_visit(net, node_colour, tree, adj_id);
    }
  }

  node_colour[init_node] = colour::black;
}
