#include "event_listener.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <base/events/types.hpp>

c_event_listener::c_event_listener(e_node_event_type _type, c_node *_node, std::function<void(c_node_event *event)> &_callback) : type(_type), node(_node), callback(std::move(_callback))
{
    _listeners.push_back(this);

    if (type == e_node_event_type::mouse_move_event)
    {
        priority = 1;
    }

    std::sort(_listeners.begin(), _listeners.end(),
              [](const c_event_listener *event_a, c_event_listener *event_b)
              {
                  return event_a->priority > event_b->priority;
              });

    std::cout << "Created event listener " << (int)_type << std::endl;
}

c_event_listener::~c_event_listener()
{
    auto itx = std::find(_listeners.begin(), _listeners.end(), this);
    if (itx != _listeners.end())
    {
        _listeners.erase(itx);
        std::cout << "Destroyed event listener " << std::endl;
    }
}