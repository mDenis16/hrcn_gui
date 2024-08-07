#pragma once
#include <deque>
#include <vector>
#include <functional>
#include <blend2d.h>

#include <mutex>

#include "node.hpp"
#include "style/style_manager.hpp"
#include <utils/fnvhash.hpp>
class c_transition;
class c_node_event;
class c_event_listener;
class c_mouse_move_event;
class c_node;
class c_font;
class c_state;

enum class e_position : uint8_t;

class c_app_context
{
public:
    c_app_context(int width, int height);

    int width = 0;
    int height = 0;
    bool _enableHighDPI = false;
    float _DPIscaleFactor = 1.f;

    ~c_app_context();

    std::vector<c_transition *> _transitions;

    std::deque<c_node_event *> _events;

    std::vector<c_event_listener *> _event_listeners;

    std::vector<c_node *> _nodes;

    std::vector<c_font *> _fonts;

    std::vector<c_state* > _states;

    bool modified = false;

    void ensure_state_exist(c_state* state);

    void add_state(c_state* state);

    void enableHighDPI(float scaleFactor);


    void execute();

    void process_events();

    void process_event(c_node_event *event);

    void process_mouse_move(c_mouse_move_event *event);

    void process_event_for_listeners(c_node_event *event, std::vector<c_event_listener *> listeners, bool absolute = false);

    void push_event(c_node_event *_event);

    void add_event_listener(c_node *node, c_event_listener *listener);
    void remove_event_listener(c_event_listener *listener);
    void remove_event_listeners_for_node(c_node *node);
    void remove_transitions_for_node(c_node *node);
    std::recursive_mutex _context_mutext;


    bool dirty_context = false;

    inline bool is_context_dirty() {
        return dirty_context;
    }

    float delta_time = 0.f;
    void mark_context_dirty() {
        dirty_context = true;
    }
    BLImage texture;
    std::vector<uint8_t> image_buffer;
    std::vector<uint8_t>& get_image_buffer();
    bool render();
    void set_node_root(c_node *node);

    c_node * root = nullptr;

    template <str_to_hash str>
    c_node* get_node_by_hash() {
        constexpr std::uint32_t hash = string_to_fnv1_hash<str>();
        return get_node_by_hash(hash);
    }
    c_node* get_node_by_hash(std::uint32_t hash);

    c_node* last_rendered = nullptr;
    inline static c_app_context *_current_context = nullptr;

    void add_node(c_node *node);


    void remove_node(c_node *node)
    {
        _nodes.erase(std::remove_if(_nodes.begin(), _nodes.end(), [node](c_node *nd)
                                    { return nd == node; }));

        std::sort(_nodes.begin(), _nodes.end(), [](c_node* a, c_node* b) {
        return a->style().get_z_index() < b->style().get_z_index();
    });
        for(int i = 0; i < _nodes.size(); i++) {
            _nodes.at(i)->global_index = i;
        }
    }

    void for_each_node_if(std::function<bool(c_node *)> _if_callback, std::function<void(c_node *)> _callback);

    c_node *find_target_for_event(c_node_event *event);

    inline static c_app_context *get_current()
    {
        return _current_context;
    }
    inline static void set_current(c_app_context *_ctx)
    {
        _current_context = _ctx;
    }
};
