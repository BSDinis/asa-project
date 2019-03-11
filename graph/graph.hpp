/***
 * graph.hpp
 *
 * graph interface
 */
#ifndef __GRAPH
#define __GRAPH

#include <iostream>
#include <vector>

namespace graph {
  template <typename T>
  class graph {
    int edges;
    std::vector<T> nodes;
    std::vector<std::vector<bool>> adj;

    public:
      graph();
      graph(int n) : nodes{n}, adj{n, std::vector<bool>(n)} {}
      // graph(std::vector<T> nodes);
      ~graph() = default;

      bool add_edge(const int from, const int to);
      bool add_biedge(const int a, const int b);
      bool rem_edge(const int from, const int to);
      bool rem_biedge(const int a, const int b);

      int add_vertex(T && vertex);
      int add_vertex(T & vertex);

      const T& get_vertex(int index) const;
      int n_vertices() const;
      int n_edges() const;
      friend std::ostream & operator<<(std::ostream &os, const graph<T> &g) {
        int edge = 0;
        int n_vertices = g.nodes.size();
        for (int i = 0; i < n_vertices; i++) {
          for (int j = 0; j < n_vertices; j++) {
            if (g.adj[i][j]) {
              os << edge++ << "\t: [ " << i << " -> " << j << " ]\n";
            }
          }
        }
        return os << n_vertices << " vertices\n";
      }
  };

  /***
   * implementationc
   */

  template<typename T>
  graph<T>::graph() : edges(0)
  {
    for (auto line : adj)
      for (auto el : line)
        el = false;
  }

  template<typename T>
  bool graph<T>::add_edge(const int from, const int to)
  {
    if (from >= n_vertices() || to >= n_vertices()) return false;
    if (adj[from][to] == false) edges++;
    adj[from][to] = true;
    return true;
  }

  template<typename T>
  bool graph<T>::add_biedge(const int from, const int to)
  {
    if (from >= n_vertices() || to >= n_vertices()) return false;
    if (adj[from][to] == false) edges++;
    if (adj[to][from] == false) edges++;
    adj[from][to] = adj[to][from] = true;
    return true;
  }

  template<typename T>
  bool graph<T>::rem_edge(const int from, const int to)
  {
    if (from >= n_vertices() || to >= n_vertices()) return false;
    if (adj[from][to] == true) edges--;
    adj[from][to] = false;
    return true;
  }

  template<typename T>
  bool graph<T>::rem_biedge(const int from, const int to)
  {
    if (from >= n_vertices() || to >= n_vertices()) return false;
    if (adj[from][to] == true) edges--;
    if (adj[to][from] == true) edges--;
    adj[from][to] = adj[to][from] = false;
    return true;
  }

  template<typename T>
  int graph<T>::add_vertex(T & vertex)
  {
    nodes.emplace_back(vertex);
    for (auto line : adj)
      line.emplace_back(false);

    adj.emplace_back(nodes.size(), false);

    return nodes.size() - 1;
  }

  template<typename T>
  int graph<T>::add_vertex(T && vertex) { return add_vertex(vertex); }

  template<typename T>
  const T& graph<T>::get_vertex(int index) const { return nodes[index]; }

  template<typename T>
  int graph<T>::n_vertices() const { return nodes.size(); }

  template<typename T>
  int graph<T>::n_edges() const { return edges; }
}

#endif
