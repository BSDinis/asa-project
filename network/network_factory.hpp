/**
 * router_factory.hpp
 *
 * create router from input file
 */
#pragma once

#include "network.hpp"
#include <fstream>
#include <iostream>

network create_network(std::string filename);
network create_network(std::istream &in);
