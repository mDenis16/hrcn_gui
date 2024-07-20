#pragma once
#include <functional>
#include <mutex>
class c_node;

class c_node_event;
enum class e_node_event_type : uint8_t;

class c_event_listener
{

public:
    c_node *node;
    uint8_t priority = 0;
    e_node_event_type type;

    int z_index = 0;
    bool absolute = false;
    std::function<void(c_node_event *event)> callback;


    c_event_listener(e_node_event_type _type, c_node *_node, std::function<void(c_node_event *event)> _callback);
    ~c_event_listener();
    

    

};
