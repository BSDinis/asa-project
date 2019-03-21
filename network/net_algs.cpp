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

inline bool is_root(
    const int node,
    const dfs_help & dh
    )
{ return dh.parent[node] < 0; }

inline bool is_articulation_point(
    const int node,
    const int adj,
    const int n_children,
    const struct dfs_help & dh
    )
{ return dh.articulation[node] ||
  (is_root(node, dh) && n_children >= 2) ||
    (!is_root(node, dh) && dh.low[adj] >= dh.discovery[node]); }

static void dfs_tarjan_visit(
    const network &net,
    std::vector<network::colour> &node_colour,
    struct dfs_help &dh,
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
      dfs_tarjan_visit(net, node_colour, dh, adj_id);

      if ( dh.low[adj_id] < dh.low[init_node] )
        dh.low[init_node] = dh.low[adj_id];

      if ( is_articulation_point(init_node, adj_id, n_childs, dh) )
        dh.articulation[init_node] = true;
    }
    else if ( adj_id != dh.parent[init_node] && dh.discovery[adj_id] < dh.low[init_node] )
        dh.low[init_node] = dh.discovery[adj_id];
  }
}

std::vector<int> dfs_tarjan(
    const network &net,
    std::vector<int> &articulation_pts
    ) noexcept
{
  using colour=network::colour;
  using std::vector;

  vector<int> ids;
  vector<colour> node_colour(net.n_nodes(), colour::white);

  struct dfs_help dh(net);

  ssize_t nnodes = net.n_nodes();
  for (int i = nnodes - 1; i >= 0; i--) {
    if (node_colour[i] != colour::white) continue;
    ids.push_back(i); // guaranteed to be the highest id
    dfs_tarjan_visit(net, node_colour, dh, i);
  }

  for (int i = 0; i < net.n_nodes(); i++)
    if (dh.articulation[i])
      articulation_pts.push_back(i);

  return ids;
}

static void dfs_visit(const network &net,
    std::vector<network::colour> &node_colour,
    int &n_nodes,
    const int init_node) noexcept
{
  using colour=network::colour;
  using std::vector;
  node_colour[init_node] = colour::grey;
  const auto & adjacents = net.neighbours(init_node);
  for (const auto & adj_id : adjacents) {
    if ( node_colour[adj_id] == colour::white ) {
      ++n_nodes;
      dfs_visit(net, node_colour, n_nodes, adj_id);
    }
  }
}

int dfs(
    const network &net,
    const std::vector<int> &removed_pts
    ) noexcept
{
  using colour=network::colour;
  using std::vector;

  int big_subnet = 0;
  vector<colour> node_colour(net.n_nodes(), colour::white);

  for ( const auto & rem : removed_pts) // dfs ignores these nodes
    node_colour[rem] = colour::red; // FIXME, this could be merged with the other cycle

  auto nnodes = net.n_nodes();
  for (int i = nnodes - 1; i >= 0; i--) {
    if (node_colour[i] != colour::white) continue;
    int n_nodes = 1;
    dfs_visit(net, node_colour, n_nodes, i);
    if (n_nodes > big_subnet)
      big_subnet = n_nodes;
  }

  return big_subnet;
}

