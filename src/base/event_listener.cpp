#include "event_listener.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <base/events/types.hpp>
#include <base/node.hpp>


c_event_listener::c_event_listener(e_node_event_type _type, c_node *_node, std::function<void(c_node_event *event)> _callback) : type(_type), node(_node), callback(_callback)
{
    this->callback = _callback;
  

    if (type == e_node_event_type::mouse_move_event)
    {
        priority = 1;
    }

}

c_event_listener::~c_event_listener()
{

}