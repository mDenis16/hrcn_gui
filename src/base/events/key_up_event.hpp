#pragma once

#include <base/node_event.hpp>
#include <blend2d.h>

class c_key_up_event : public c_node_event {
public:
    int keycode = -1;
    c_key_up_event();
};
