#pragma once

#include <base/node_event.hpp>

class c_key_down_event : public c_node_event {
public:
    int keycode = -1;
    c_key_down_event();
};
