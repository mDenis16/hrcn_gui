#pragma once
#include <cstdint>

#include "node_event.hpp"
#include "blend2d/geometry.h"


class c_scroll_event : public c_node_event {
public:
    BLPoint offset;
    BLPointI mouse_pos;

    c_scroll_event() {
       type = e_node_event_type::min;
    }
    ~c_scroll_event() {

    }

};