#pragma once

#include <base/node_event.hpp>
#include <blend2d.h>
class c_mouse_up_event : public c_node_event
{
public:
    BLPoint position;
    c_mouse_up_event();
};
