//
// Created by Denis Topor on 05.07.2024.
//

#ifndef C_EVENT_LISTENER_H
#define C_EVENT_LISTENER_H
#include <iostream>

#include "node.hpp"
#include "node_event.hpp"

template<typename  T = c_node_event>
class c_event_listener {
public:

    c_event_listener(e_node_event_type _type, std::function<void(T* event)>& _callback) {
        type = _type;
        _callback = std::move(_callback);
    }
    e_node_event_type type;

    std::function<void(c_node* event)> _callback;
};



#endif //C_EVENT_LISTENER_H
