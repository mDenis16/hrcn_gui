#pragma once
#include <iostream>


enum class e_node_event_type : uint8_t {
   min,
   mouse_enter_event,
   mouse_exit_event,
   mouse_move_event,
   mouse_up_event,
   mouse_down_event,
   mouse_scroll_event,
   key_up_event,
   key_down_event,
   max
};

