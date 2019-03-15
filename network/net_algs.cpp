#include "net_algs.hpp"

struct dfs_help {
  int time;
  std::vector<int> parent;
  std::vector<int> discovery;
  std::vector<int> low;
  std::vector<bool> articulation;

  dfs_help( const network &net ) noexcept : time{0},
    parent(net.n_nodes(), -1),
    discovery(net.n_nodes(), 0),
    low(net.n_nodes(), 0),
    articulation(net.n_nodes(), false) {}
};

static void dfs_tarjan_visit(
    const network &net,
    std::vector<network::colour> &node_colour,
    struct dfs_help &dh,
    std::vector<int> &tree,
    const int init_node) noexcept
{
  using colour=network::colour;
  using std::vector;

  node_colour[init_node] = colour::grey;
  int n_childs = 0;
  dh.discovery[init_node] = dh.low[init_node] = ++dh.time;

  const auto & adjacents = net.neighbours(init_node);

  for (const auto & adj_id : adjacents) {
    if ( node_colour[adj_id] == colour::white ) {
      n_childs++;
      dh.parent[adj_id] = init_node;
      tree.push_back(adj_id); // add to stack

      dfs_tarjan_visit(net, node_colour, dh, tree, adj_id);

      if ( dh.low[adj_id] < dh.low[init_node] )
        dh.low[init_node] = dh.low[adj_id];

      if ( (dh.parent[init_node] <  0 && n_childs >= 2) ||
           (dh.parent[init_node] >= 0 && dh.low[adj_id] >= dh.discovery[init_node]) )
        dh.articulation[init_node] = true;
    }
    else if ( adj_id != dh.parent[init_node] && dh.discovery[adj_id] < dh.low[init_node] )
        dh.low[init_node] = dh.discovery[adj_id];
  }
}

std::vector<std::vector<int> > dfs_tarjan(
    const network &net,
    std::vector<int> &articulation_pts
    ) noexcept
{
  using colour=network::colour;
  using std::vector;

  vector<vector<int>> forest;
  vector<colour> node_colour(net.n_nodes(), colour::white);

  struct dfs_help dh(net);

  ssize_t nnodes = net.n_nodes();
  for (int i = 0; i < nnodes; i++) {
    if (node_colour[i] != colour::white) continue;
    vector<int> tree = {i};
    dfs_tarjan_visit(net, node_colour, dh, tree, i);
    forest.push_back(tree);
  }

  for (int i = 0; i < net.n_nodes(); i++)
    if (dh.articulation[i])
      articulation_pts.push_back(i);

  return forest;
}

static void dfs_visit(const network &net,
    std::vector<network::colour> &node_colour,
    std::vector<int> &tree,
    const int init_node) noexcept
{
  using colour=network::colour;
  using std::vector;
  node_colour[init_node] = colour::grey;
  const auto & adjacents = net.neighbours(init_node);
  for (const auto & adj_id : adjacents) {
    if ( node_colour[adj_id] == colour::white ) {
      tree.push_back(adj_id);
      dfs_visit(net, node_colour, tree, adj_id);
    }
  }
}

std::vector<std::vector<int>> dfs(
    const network &net,
    const std::vector<int> &removed_pts
    ) noexcept
{
  using colour=network::colour;
  using std::vector;
  vector<vector<int>> forest;
  vector<colour> node_colour(net.n_nodes(), colour::white);

  for ( const auto & rem : removed_pts) // dfs ignores these nodes
    node_colour[rem] = colour::red;

  auto nnodes = net.n_nodes();
  for (int i = 0; i < nnodes; i++) {
    if (node_colour[i] != colour::white) continue;
    vector<int> tree = {i};
    dfs_visit(net, node_colour, tree, i);
    forest.push_back(tree);
  }

  return forest;
}

