//
// Created by Denis Topor on 05.07.2024.
//

#ifndef MOUSE_ENTER_EVENT_H
#define MOUSE_ENTER_EVENT_H
#include <base/node_event.hpp>


class c_mouse_enter_event : public c_node_event {
public:
    c_mouse_enter_event() {
        type = e_node_event_type::mouse_enter;
    }
};



#endif //MOUSE_ENTER_EVENT_H
