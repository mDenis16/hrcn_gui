#pragma once
#include <yoga/Yoga.h>
#include <blend2d.h>
#include <vector>
#include <functional>
#include "node_event.hpp"
#include <iostream>
#include <chrono>

#include <utils/fnvhash.hpp>

class c_style_manager;
class c_transitions_manager;
class c_event_listener;

enum class e_node_event_type : uint8_t;

class c_node
{
private:
    /* data */

    c_transitions_manager *_transitions;

public:
    c_node(/* args */);
    ~c_node();

    bool mouse_hover = false;

    virtual void render(BLContext &context);

    std::vector<c_event_listener *> _event_listeners;

    c_style_manager *_style;
    c_style_manager &style()
    {
        return *_style;
    }

    bool is_root = false;
    int child_index = 0;

    inline c_transitions_manager &transitions(int ms);

    int biggest_z_index = 0;

    c_node *parent = nullptr;
    int z_index = 0;

    bool dirty_layout = false;

    float scroll = 0.f;
    float max_scroll = 0.f;
    float totalContentSize = 0.f;

    bool overflow_y = false;
    std::vector<c_node *> children;

    std::uint32_t identifier = -1;

    c_event_listener *add_event_listener(e_node_event_type type, std::function<void(c_node_event *)> _fn);
    // void remove_event_listener(c_event_listener* ev_listener);

    inline static std::vector<c_node *> nodes;

    void layout_update(BLPointI point);

    virtual void add_child(c_node *node);

    virtual void on_event(c_node_event *event);

    void handle_event(c_node_event *event);

    BLRect calc_total_size();

    BLSize content_size();

    BLRect _content;
    bool dirty = true;
    bool layout_dirty = true;

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

    template <str_to_hash str>
    __inline void set_node_identifier()
    {
        constexpr std::uint32_t hash = string_to_fnv1_hash<str>();
        identifier = hash;
    }
    template <str_to_hash str>
    static c_node *get_node_by_hash()
    {
        constexpr std::uint32_t hash = string_to_fnv1_hash<str>();

        for (auto &node : nodes)
            if (node->identifier == hash)
                return node;

        return nullptr;
    }

    bool require_rerender(bool& _dirty_layout);

    bool hovering = false;

    BLRectI box;
    BLRect static_box;

    BLRgba32 bg_color;

    BLRgba32 border_color;

    YGNodeRef node_ref;

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
