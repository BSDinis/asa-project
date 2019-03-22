#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstddef>


class network {
  std::vector<std::vector<int>> links;

  public:
    enum class colour { white = 0, grey, black, green, red };
    network() noexcept {}
    network(int n) noexcept : links(static_cast<size_t>(n)) // reserve space for needed links
    {}

    network(ssize_t n) noexcept : network{static_cast<int>(n)} {}
    network(size_t n) noexcept : network{static_cast<int>(n)} {}
    ~network() = default;

    bool add_link(const int u, const int v) noexcept
    {
      if (u >= n_nodes() || v >= n_nodes()) return false;
      if (u == v || has_link(u, v)) return true;
      links[u].push_back(v);
      links[v].push_back(u);
      return true;
    }

    inline bool rem_link(const int u, const int v) noexcept
    {
      if (u >= n_nodes() || v >= n_nodes() || u == v) return false;
      auto it1 = std::find(links[u].cbegin(), links[u].cend(), v);
      auto it2 = std::find(links[v].cbegin(), links[v].cend(), u);
      if (it1 != links[u].end()) links[u].erase(it1);
      if (it2 != links[v].end()) links[v].erase(it2);
      return true;
    }

    inline bool has_link(const int u, const int v) const noexcept
    {
      return (u < n_nodes() && u >= 0 && v < n_nodes() && v >= 0)
          && ( u == v || std::find(links[u].cbegin(), links[u].cend(), v) != links[u].end());
    }

    inline const std::vector<int> &neighbours(const int u) const noexcept
    {
      if (u >= n_nodes() || u < 0) std::vector<int>();
      return links[u];
    }

    inline void add_node() noexcept { links.emplace_back(); }
    inline int n_nodes() const noexcept { return links.size(); }
};

std::ostream & operator<<(std::ostream &os, const network &n) noexcept;

network create_network(std::istream &in) noexcept;

inline network create_network(const std::string &filename) noexcept;



std::vector<int> dfs_tarjan(
    const network &net,
    std::vector<int> &articulation_pts
    ) noexcept ;

int dfs(
    const network &net,
    const std::vector<int> &removed_pts
    ) noexcept ;

void first_part(const network & net, std::vector<int> &articulation_pts);
void second_part(const network & net, const std::vector<int> &articulation_pts);

int main()
{
  const auto &net = create_network(std::cin);
  std::vector<int> articulation_pts;
  first_part(net, articulation_pts); // compute articulation pts
  std::cout << dfs(net, articulation_pts) << '\n'; // remove articulation pts and calc max subnet
  return 0;
}

// hack: this forces the stack size to be controlled (clears the stack before the seconde dfs)
void first_part(const network & net, std::vector<int> &articulation_pts)
{
  const auto ids = dfs_tarjan(net, articulation_pts);

  std::cout << ids.size() << '\n';
  for (ssize_t i = ids.size() - 1; i >= 0; i--) {
    const auto &id = ids[i];
    std::cout << id+1; // get it normalized
    if (i != 0) std::cout << ' ';
  }

  std::cout << '\n' << articulation_pts.size() << '\n';
}

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

static inline bool is_root(
    const int node,
    const dfs_help & dh
    )
{ return dh.parent[node] < 0; }

static inline bool is_articulation_point(
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

