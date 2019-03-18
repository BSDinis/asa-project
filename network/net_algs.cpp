#include "net_algs.hpp"

struct dfs_help {
  int time, max_sub_rem;
  std::vector<int> parent; // id of the parents
  std::vector<int> discovery; // time of discovery
  std::vector<int> low; // lower time of the component
  std::vector<int> n_descendant_nodes; // size of the component of the subnet formed by descendants until articulation pt
  std::vector<bool> articulation;

  dfs_help( const network &net ) noexcept : time{0}, max_sub_rem{0},
    parent(net.n_nodes(), -1),
    discovery(net.n_nodes(), 0),
    low(net.n_nodes(), 0),
    n_descendant_nodes(net.n_nodes(),0),
    articulation(net.n_nodes(), false) {}
};

static inline bool is_articulation_point(
    const struct dfs_help &dh,
    const int node, const int n_visited,
    const int adj)
{
  return dh.articulation[node]
    || ( dh.parent[node] < 0 && n_visited >= 2 )
    || ( dh.parent[node] >= 0 && dh.low[adj] >= dh.discovery[node]);
}

static void dfs_tarjan_visit(
    const network &net,
    std::vector<network::colour> &node_colour,
    struct dfs_help &dh,
    const int init_node ) noexcept
{
  using colour=network::colour;
  using std::vector;

  node_colour[init_node] = colour::grey;
  dh.discovery[init_node] = dh.low[init_node] = ++dh.time;
  int n_childs = 0;

  dh.n_descendant_nodes[init_node] = 1;
  dh.max_sub_rem = std::max(dh.max_sub_rem, dh.n_descendant_nodes[init_node]);

  const auto & adjacents = net.neighbours(init_node);
  for (const auto & adj_id : adjacents) {
    if ( node_colour[adj_id] == colour::white ) {
#ifdef DEBUG
      std::clog << init_node+1 << " found " << adj_id+1 << '\n';
#endif
      n_childs++;
      dh.parent[adj_id] = init_node;
      dfs_tarjan_visit(net, node_colour, dh, adj_id);

      if ( is_articulation_point(dh, init_node, n_childs, adj_id) ) {
        dh.articulation[init_node] = true;
        dh.n_descendant_nodes[init_node] = 0;
        if ( node_colour[adj_id] != colour::red )
          node_colour[adj_id] = colour::green;
      }
      else
        dh.n_descendant_nodes[init_node] += dh.n_descendant_nodes[adj_id];

      if ( dh.low[adj_id] < dh.low[init_node] )
        dh.low[init_node] = dh.low[adj_id];
    }
    else {
      if ( adj_id != dh.parent[init_node] && dh.discovery[adj_id] < dh.low[init_node] )
        dh.low[init_node] = dh.discovery[adj_id];
      if ( node_colour[adj_id] == colour::green ){
        dh.n_descendant_nodes[init_node] += dh.n_descendant_nodes[adj_id];
        node_colour[adj_id] = colour::red;
      }
    }

    dh.max_sub_rem = std::max( dh.max_sub_rem, dh.n_descendant_nodes[adj_id]);
  }
}

std::vector<int> dfs_tarjan(
    const network &net,
    int &n_articulation_pts,
    int &max ) noexcept
{
  using colour=network::colour;
  using std::vector;

  n_articulation_pts=0;

  vector<int> ids;
  vector<colour> node_colour(net.n_nodes(), colour::white);

  struct dfs_help dh(net);

  ssize_t nnodes = net.n_nodes();
  for (int i = nnodes - 1; i >= 0; i--) {
    if (node_colour[i] != colour::white) continue;
    ids.push_back(i); // guaranteed to be the highest id

    dfs_tarjan_visit(net, node_colour, dh, i);
    if ( dh.n_descendant_nodes[i] > dh.max_sub_rem )
      dh.max_sub_rem = dh.n_descendant_nodes[i];
  }

  max = dh.max_sub_rem;

  for (int i = 0; i < net.n_nodes(); i++)
    if (dh.articulation[i]) {
      n_articulation_pts++;
    }

  return ids;
}
