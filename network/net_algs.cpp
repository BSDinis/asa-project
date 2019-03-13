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

struct dfs_help {
  int time;
  std::vector<int> parent;
  std::vector<int> discovery;
  std::vector<int> low;

  dfs_help( const network &net ) : time{},
    parent(net.n_nodes(), -1),
    discovery(net.n_nodes()),
    low(net.n_nodes()) {}
};

static void dfs_tarjan_visit(const network &net,
    std::vector<int> &articulation_pts,
    std::vector<network::colour> &node_colour,
    struct dfs_help &dh,
    std::vector<int> &tree,
    const int init_node);

std::vector<std::vector<int>> dfs_tarjan(
    const network &net,
    std::vector<int> &articulation_pts
    )
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
    dfs_tarjan_visit(net, articulation_pts, node_colour, dh, tree, i);
    forest.push_back(tree);
  }

  return forest;
}

static void dfs_tarjan_visit(const network &net,
    std::vector<int> &articulation_pts,
    std::vector<network::colour> &node_colour,
    struct dfs_help &dh,
    std::vector<int> &tree,
    const int init_node)
{
  using colour=network::colour;
  using std::vector;

  node_colour[init_node] = colour::grey;
  int n_childs = 0;
  dh.discovery[init_node] = dh.low[init_node] = ++dh.time;

  std::vector<int> adjacents = neighbour_routers(net, init_node);
  for (int adj_id : adjacents) {
    if ( node_colour[adj_id] == colour::white ) {
      n_childs++;
      dh.parent[adj_id] = init_node;
      tree.push_back(adj_id);
      dfs_tarjan_visit(net, articulation_pts, node_colour, dh, tree, adj_id);

      if ( dh.low[adj_id] < dh.low[init_node] )
        dh.low[init_node] = dh.low[adj_id];

      if ( (dh.parent[init_node] <  0 && n_childs >= 2) ||
           (dh.parent[init_node] >= 0 && dh.low[adj_id] >= dh.discovery[init_node]) )
        articulation_pts.push_back(init_node); // allows duplicates
    }
    else if ( adj_id != dh.parent[init_node] && dh.discovery[adj_id] < dh.low[init_node] )
        dh.low[init_node] = dh.discovery[adj_id];  
  }
}
/*------------------------------------------------------*/
static void dfs_visit(const network &net,
    std::vector<network::colour> &node_colour,
    std::vector<int> &tree,
    const int init_node);

std::vector<std::vector<int>> dfs(
    const network &net,
    std::vector<int> &removed_pts
    )
{
  using colour=network::colour;
  using std::vector;
  vector<vector<int>> forest;
  vector<colour> node_colour(net.n_nodes(), colour::white);

  for ( int rem : removed_pts) // dfs ignores these nodes
    node_colour[rem] = colour::red;

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
}