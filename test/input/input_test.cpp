#include "network.hpp"
#include <iostream>
#include <vector>

enum class colour { white = 0, grey, black };

void dfs_visit(const network & net,
    std::vector<colour> & node,
    const int node_id,
    int &subnet_maxid );

int main()
{
  network net = create_network(std::cin);
  std::cout << net;

  int n_sub_nets = 0;
  std::vector<int> id_sub_net;
  std::vector<colour> node_colour(net.n_nodes(), colour::white);

  for (int i = 0; i < net.n_nodes() ; ++i) {
  	if (node_colour[i] == colour::white ) {
  		int subnet_maxid = i;
  		dfs_visit(net, node_colour, i, subnet_maxid );
  		n_sub_nets++;
  		id_sub_net.push_back(subnet_maxid);
  	}
  }

  std::cout << "number of subnets : " << n_sub_nets << std::endl << "sub net ids : ";
  for (int i = 0; i < (int)id_sub_net.size(); i++)
  	std::cout << id_sub_net[i]+1 << " ";

  std::cout << std::endl;

}
void dfs_visit(const network & net,
    std::vector<colour> & node_colour,
    const int node_id,
    int &subnet_maxid )
{
  node_colour[node_id] = colour::grey;

  std::vector<int> adjacents = neighbour_routers(net, node_id);
  for ( int adj_id : adjacents ) {
    if ( node_colour[adj_id] == colour::white ) {
      if ( subnet_maxid < node_id )
        subnet_maxid = node_id;

      dfs_visit( net, node_colour, adj_id, subnet_maxid );
    }
  }

  node_colour[node_id] = colour::black;
}
