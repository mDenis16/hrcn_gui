#pragma once
#include <base/node_event.hpp>
#include <blend2d.h>


class c_mouse_scroll_event : public c_node_event {
public:
    BLPoint offset;
    c_mouse_scroll_event();
};

