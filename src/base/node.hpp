#pragma once
#include <cassert>
#include <yoga/Yoga.h>
#include <blend2d.h>
#include <vector>
#include <functional>
#include "node_event.hpp"
#include <iostream>
#include <algorithm>
#include <chrono>

#include <utils/fnvhash.hpp>


#include "effect.hpp"
#include "style/style_manager.hpp"

class c_app_context;
class c_border;
class c_style_manager;
class c_transitions_manager;
class c_event_listener;
class c_effect;
class c_state;
class c_font;


enum class e_node_event_type : uint8_t;

class c_node_ref;

class c_pending_state {
public:

    std::vector<c_event_listener *> _event_listeners;
    std::vector<c_state *> _states;
    std::vector<c_effect *> _effects;

    c_node* _node = nullptr;

    c_pending_state(c_node* node) {
        _node = node;
    }



    void consume();
    inline bool is_consumed() { return _consumed;}

    void add_event_listener(c_node *node, c_event_listener *listener);

    void add_effect(c_node* node, c_effect* effect);
    void add_state( c_state* state);

    bool _consumed = false;
};

class c_node
{
private:
    /* data */

    c_transitions_manager *_transitions;

public:
    c_node(/* args */);
    ~c_node();


    bool _dirty_border = false;

    inline bool is_border_dirty() {
        return _dirty_border;
    }


    std::array<BLPath, 4> _border_paths;

   inline static c_font* default_font = nullptr;
    bool have_rounded_borders() ;
    std::string debug_obj_descriptor;

    BLPath round_rect;

    void set_debug_descriptor(std::string s) {
        debug_obj_descriptor = s;
    }

    bool is_text = false;

    int global_index = 0;

    bool _registered_in_collector = false;

    c_app_context *app_context = nullptr;

    bool mouse_hover = false;

    virtual void render(BLContext &context);

    c_event_listener* scroll_listener = nullptr;


    std::vector<c_event_listener *> _event_listeners;

    c_style_manager *_style;
    c_style_manager &style()
    {
        return *_style;
    }

    bool is_root = false;
    int child_index = 0;

    c_transitions_manager &transitions(int ms);

    int biggest_z_index = 0;

    c_node *parent = nullptr;

    c_pending_state* _pending = nullptr;

    void* getRef() {
        return (void*)node_ref;
    }

    bool dirty_layout = true;
    bool dirty = true;

    float scroll = 0.f;
    float max_scroll = 0.f;
    float totalContentSize = 0.f;

    bool overflow_y = false;
    std::vector<c_node *> children;

    std::uint32_t identifier = -1;

    c_event_listener *add_event_listener(e_node_event_type type, std::function<void(c_node_event *)> _fn);
    void remove_event_listener(c_event_listener *_event_listener);

    

    virtual void layout_update(BLPointI point);

    virtual void add_child(c_node *node);

    virtual void remove_child (c_node *node);
    virtual void on_event(c_node_event *event);


    void handle_event(c_node_event *event);
    void safe_destroy();
    BLRect calc_total_size();

    BLSize content_size();

    BLRect _content;

    void destroy();

    void clear();
    // void update_transitions();



    BLRect calculate_bounding_box_of_children();

    BLRect content_box;

    BLRect total_box;
    inline void mark_as_dirty()
    {
        dirty = true;
    }
    inline void mark_layout_as_dirty()
    {
        dirty_layout = true;
    }
    bool is_dirty()
    {
        return dirty;
    }

    bool is_layout_dirty()
    {
        return dirty_layout;
    }

    void sync_context();


    std::vector<c_state *> _states;
    std::vector<c_effect *> _effects;

    void use_state(c_state *state);

    void use_effect(std::function<void()> _callback, std::vector<c_state *> _states);

    void check_for_state_changes();

    template <str_to_hash str>
    __inline void set_node_identifier()
    {
        constexpr std::uint32_t hash = string_to_fnv1_hash<str>();
        identifier = hash;
    }




    bool require_rerender(bool &_dirty_layout);

    bool absolute_anchestor(int& z_index);

    void propagate_context(c_app_context* context);

    bool hovering = false;

    std::function<void()> _on_init;
    bool _init =false;
    void bind_init(std::function<void()> _callback) {
        _on_init = _callback;
    }
    void on_init(std::function<void()> _callback) {
        _on_init = _callback;
    }

    BLRectI box;
    BLRect static_box;

  


    bool absolute = false;


    c_node_ref* node_ref;

    std::function<void(c_node *item)> _click;

    std::function<void(c_node *item, BLPointI mouse)> _mouse_move;

    std::function<void(c_node *item)> _mouse_enter;
    std::function<void(c_node *item)> _mouse_leave;

    bool _force_listen_to_mouse_move = false;
    void force_listen_to_mouse_move() { _force_listen_to_mouse_move = true; }

    inline void mouse_enter(std::function<void(c_node *item)> _fn)
    {
        _mouse_enter = _fn;
    }
    inline void mouse_leave(std::function<void(c_node *item)> _fn)
    {
        _mouse_leave = _fn;
    }
    inline void mouse_move(std::function<void(c_node *item, BLPointI mouse)> _fn, bool capture_all = false)
    {
        _mouse_move = _fn;
    }

    void click_listener(std::function<void(c_node *item)> _fn)
    {
        _click = _fn;
    }
};
