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

   /* The `std::sort` function is sorting the `_listeners` vector of `c_event_listener` objects based
   on the `priority` member variable of each object. The lambda function provided to `std::sort`
   defines the custom comparison logic for sorting the objects. In this case, it is sorting the
   objects in descending order of their `priority` values. */
    // std::sort(_listeners.begin(), _listeners.end(),
    //           [](const c_event_listener *event_a, c_event_listener *event_b)
    //           {
    //               return event_a->priority > event_b->priority;
    //           });

    std::cout << "Created event listener " << _node->app_context << std::endl;
}

c_event_listener::~c_event_listener()
{
    //   std::lock_guard<std::mutex> guard(_mtx);
      
    // auto itx = std::find(_listeners.begin(), _listeners.end(), this);
    // if (itx != _listeners.end())
    // {
    //     _listeners.erase(itx);
    //     std::cout << "Destroyed event listener " << std::endl;
    // }
}