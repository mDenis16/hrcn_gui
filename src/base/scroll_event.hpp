#pragma once
#include <cstdint>

#include "node_event.hpp"
#include "blend2d/geometry.h"


class c_scroll_event : public c_node_event {
public:
    BLPoint offset;
    BLPointI mouse_pos;

    c_scroll_event() {
       ev_type = e_event_type::scroll;
    }
    ~c_scroll_event() {

    }

};