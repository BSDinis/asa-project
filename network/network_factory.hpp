/**
 * router_factory.hpp
 *
 * create router from input file
 */

#include <iostream>
#include <fstream>
#include "graph.hpp"

namespace graph
{
  using router_id = int;
  graph<router_id> create_router(std::string filename);
  graph<router_id> create_router(std::istream &in);
}
