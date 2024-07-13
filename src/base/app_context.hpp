#pragma once
#include <deque>
#include <vector>

#include <mutex>

class c_transition;
class c_node_event;
class c_event_listener;
class c_node;

class c_app_context
{
public:
    c_app_context();
    ~c_app_context();

    std::vector<c_transition *> _transitions;

    std::deque<c_node_event *> _events;

    std::vector<c_event_listener *> _event_listeners;

    void execute();

    void process_events();

    void process_event(c_node_event *event);

    void push_event(c_node_event *_event);

    void add_event_listener(c_node *node, c_event_listener *listener);
    void remove_event_listener( c_event_listener *listener);
    void remove_event_listeners_for_node(c_node* node);
void remove_transitions_for_node(c_node *node);
    std::recursive_mutex _context_mutext;

    inline static c_app_context* _current_context = nullptr;

   inline static c_app_context* get_current() {
        return _current_context;
    }
    inline static void set_current(c_app_context* _ctx){
        _current_context = _ctx;
    }
};
