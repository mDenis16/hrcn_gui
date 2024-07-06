//
// Created by Denis Topor on 05.07.2024.
//

#ifndef MOUSE_ENTER_EVENT_H
#define MOUSE_ENTER_EVENT_H
#include <base/node_event.hpp>
#include <blend2d/blend2d.h>


class c_mouse_exit_event : public c_node_event {
public:

    c_mouse_exit_event() {
        type = e_node_event_type::mouse_exit;
    }
};



#endif //MOUSE_ENTER_EVENT_H
