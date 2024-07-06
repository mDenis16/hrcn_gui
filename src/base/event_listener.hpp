#pragma once
#include <functional>

class c_node;

class c_node_event;
enum class e_node_event_type : uint8_t;

class c_event_listener
{

public:
    c_node *node;
    uint8_t priority = 0;
    e_node_event_type type;

    std::function<void(c_node_event *event)> callback;

    c_event_listener(){};

    c_event_listener(e_node_event_type _type, c_node *_node, std::function<void(c_node_event *event)> &_callback);
    ~c_event_listener();
    
    inline static std::vector<c_event_listener*> _listeners;

};
