#include "network.hpp"
#include <iostream>
#include <vector>

void visit( network::network_t & net, int vertex, int* subnet_maxid );

int main()
{
  network n = create_network(std::cin);
  std::cout << n;
  
  int n_sub_nets = 0;
  std::vector<int> id_sub_net;

  int i;
  for ( i=0; i < net.n_vertices() ; ++i)
  	net.get_vertex(i).set_white();

  for ( i=0; i < net.n_vertices() ; ++i)
  {
  	if ( net.get_vertex(i).is_white() )
  	{
  		int subnet_maxid = i;
  		visit( net, i, &subnet_maxid );
  		n_sub_nets++;
  		id_sub_net.emplace_back(subnet_maxid);
  	}
  }

  std::cout << "number of subnets : " << n_sub_nets << std::endl << "sub net ids : ";
  for (int i = 0; i < (int)id_sub_net.size(); i++)
  	std::cout << id_sub_net[i]+1 << " ";

  std::cout << std::endl; 

}
void visit( network & net, int vertex, int* subnet_maxid )
{
	net.get_vertex(vertex).set_grey();

	for ( int node : net.get_adjacents(vertex) )
		if ( net.get_vertex(node).is_white() )
		{
			if ( *subnet_maxid < node ) *subnet_maxid = node;
			visit( net, node, subnet_maxid );
		}

	net.get_vertex(vertex).set_black();
}