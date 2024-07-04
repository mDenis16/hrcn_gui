#pragma once
#include <cstdint>

#include "node_event.hpp"
#include "blend2d/geometry.h"

enum class e_keyboard_event_type : uint8_t {
    min,
    key_press,
    key_release,
    max
};
class c_keyboard_event : public c_node_event {
public:
    e_keyboard_event_type keyboard_event_type;

    int key;

    c_mouse_event() {

    }
    ~c_mouse_event() {

    }
    inline int getKey() {
        return key;
    }

};