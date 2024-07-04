#pragma once
#include <cstdint>

#include "node_event.hpp"
#include "blend2d/geometry.h"

enum class e_mouse_event_type : uint8_t {
    min,
    onclick,
   ondblclick,
   onmousedown,
   onmouseenter,
   onmouseleave,
   onmousemove,
   onmouseout,
   onmouseover,
   onmouseup,
    max
};
class c_mouse_event : public c_node_event {
public:
    e_mouse_event_type mouse_event_type;
    BLPointI position;

    bool consumed = false;

    inline void mark_as_consumed() {
        consumed = true;
    }

    c_mouse_event() {

    }
    ~c_mouse_event() {

    }
    inline int getX() {
        return position.x;
    }

    inline int getY() {
        return position.y;
    }
};