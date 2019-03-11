/**
 * router_factory.hpp
 *
 * create router from input file
 */

#include "graph.hpp"
#include <fstream>
#include <iostream>

namespace network
{
  using router_id = int;
  using network_t = graph::graph<router_id>;
  network_t create_network(std::string filename);
  network_t create_network(std::istream &in);
}
