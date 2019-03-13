/***
 * node.hpp
 *
 * node interface
 */

#ifndef __NODE
#define __NODE

#include <iostream>
#include <vector>

namespace node {

  class node {
    int colour = 0;

  public:
    node() {}
    ~node() {}

    bool is_white() const { return colour == 0; }
    bool is_grey() const { return colour == 1; }
    bool is_black() const { return colour == 2; }

    void set_white() { colour = 0;}
    void set_grey() { colour = 1; }
    void set_black() { colour = 2; }

  };

}

#endif
