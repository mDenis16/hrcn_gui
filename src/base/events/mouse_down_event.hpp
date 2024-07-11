#pragma once 

#include <base/node_event.hpp>
#include <blend2d.h>

class c_mouse_down_event : public c_node_event {
public:
      BLPointI position;
    c_mouse_down_event();
};
