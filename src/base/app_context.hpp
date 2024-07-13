#pragma once
#include <deque>
#include <vector>
#include <functional>

#include <mutex>

class c_transition;
class c_node_event;
class c_event_listener;
class c_mouse_move_event;
class c_node;
enum class e_position : uint8_t;


class c_app_context
{
public:
    c_app_context();
    ~c_app_context();

    std::vector<c_transition *> _transitions;

    std::deque<c_node_event *> _events;

    std::vector<c_event_listener *> _event_listeners;

    std::vector<c_node *> _nodes;


    void execute();

    void process_events();

    void process_event(c_node_event *event);

    void process_mouse_move(c_mouse_move_event* event);
    

    void process_event_for_listeners(c_node_event* event, std::vector<c_event_listener*> listeners, bool absolute = false );

    void push_event(c_node_event *_event);

    void add_event_listener(c_node *node, c_event_listener *listener);
    void remove_event_listener(c_event_listener *listener);
    void remove_event_listeners_for_node(c_node *node);
    void remove_transitions_for_node(c_node *node);
    std::recursive_mutex _context_mutext;

    inline static c_app_context *_current_context = nullptr;

    void add_node(c_node *node)
    {
        _nodes.push_back(node);
    }

    void remove_node(c_node *node)
    {
        _nodes.erase(std::remove_if(_nodes.begin(), _nodes.end(), [node](c_node *nd)
                                          { return nd == node; }));
    }

    void for_each_node_if(std::function<bool(c_node*)> _if_callback, std::function<void(c_node*)> _callback);

    c_node* find_target_for_event(c_node_event* event);


    inline static c_app_context *get_current()
    {
        return _current_context;
    }
    inline static void set_current(c_app_context *_ctx)
    {
        _current_context = _ctx;
    }
};
