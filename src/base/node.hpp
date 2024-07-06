#pragma once
#include <yoga/Yoga.h>
#include <blend2d.h>
#include <vector>
#include <functional>
#include "node_event.hpp"
#include <iostream>

#include <utils/fnvhash.hpp>

#include "c_event_listener.h"

enum class e_flex_direction : uint8_t {
    column = YGFlexDirectionColumn,
    column_reverse = YGFlexDirectionColumnReverse,
    row = YGFlexDirectionRow,
    row_reverse = YGFlexDirectionRowReverse,
  };

enum class e_align : uint8_t {
    flex_auto = YGAlignAuto,
    flex_start = YGAlignFlexStart,
    center = YGAlignCenter,
    flex_end = YGAlignFlexEnd,
    strech = YGAlignStretch,
    baseline = YGAlignBaseline,
    space_between = YGAlignSpaceBetween,
    space_around = YGAlignSpaceAround,
    space_evenly = YGAlignSpaceEvenly,
  };
enum class e_justify : uint8_t {
    flex_start = YGJustifyFlexStart,
    center = YGJustifyCenter,
    flex_end = YGJustifyFlexEnd,
    space_between = YGJustifySpaceBetween,
    space_around = YGJustifySpaceAround,
    space_evenly = YGJustifySpaceEvenly,
  };

enum class e_gutter : uint8_t {
    column = YGGutterColumn,
    row = YGGutterRow,
    all = YGGutterAll,
  };
enum class e_edge : uint8_t {
    left = YGEdgeLeft,
        top = YGEdgeTop,
        right = YGEdgeRight,
        bottom = YGEdgeBottom,
        start = YGEdgeStart,
        end = YGEdgeEnd,
        horizontal = YGEdgeHorizontal,
        vertical = YGEdgeVertical,
        all = YGEdgeAll,
};
enum class e_display : uint8_t {
    flex = YGDisplayFlex,
    none = YGDisplayNone
};
enum class e_transition_type {
    min,
    margin,
    max
};

enum class e_position : uint8_t {
    position_type_absolute = YGPositionTypeAbsolute,
    position_type_static = YGPositionTypeStatic,
    position_type_relative = YGPositionTypeRelative
};

class c_style;
class c_transitions;

class c_node
{
private:
    /* data */
public:
    c_node(/* args */);
    ~c_node();

    virtual void render(BLContext &context);

    std::vector<c_event_listener<void>*> _event_listeners;

    c_style* _style;
    c_style& style() {
        return *_style;
    }

    bool is_root =false;
    int child_index = 0;


    c_transitions* _transitions;
    c_transitions& transitions(int ms) ;

    int biggest_z_index = 0;


    c_node* parent = nullptr;
    int z_index = 0;

    bool dirty_layout = false;


    float scroll = 0.f;
    float max_scroll = 0.f;
    float totalContentSize = 0.f;

    bool overflow_y = false;
    std::vector<c_node*> children;

    std::uint32_t identifier = -1;


    template<typename T = c_node_event>
    c_event_listener* add_event_listener(e_node_event_type type, std::function<void(T*)> _fn) {
        auto event_listener = new T(type, _fn);
        _event_listeners.push_back(event_listener);
    }
    void remove_event_listener(c_event_listener* ev_listener);

    inline static std::vector<c_node*> nodes;

    void layout_update(BLPointI point);

    virtual void add_child(c_node* node);

    virtual void on_event(c_node_event* event);

    void handle_event(c_node_event* event);

    BLRect calc_total_size();

    BLSize content_size();

    BLRect _content;
    bool dirty = true;

    BLRect calculate_bounding_box_of_children() ;

    BLRect content_box;

    BLRect total_box;
    inline void mark_as_dirty() {
        dirty = true;
    }


    bool is_dirty() {
        return  dirty;
    }



    template <str_to_hash str>
    __inline void set_node_identifier() {
        constexpr std::uint32_t hash = string_to_fnv1_hash<str>();
        identifier = hash;
    }
    template<str_to_hash str>
    static c_node * get_node_by_hash() {
        constexpr std::uint32_t hash = string_to_fnv1_hash<str>();

        for(auto& node : nodes)
            if (node->identifier == hash)
                return node;

        return nullptr;
    }

    bool require_rerender() ;


    bool hovering = false;

    BLRectI box;
    BLRect static_box;

    BLRgba32 bg_color;

    BLRgba32 border_color;

    YGNodeRef node_ref;

    std::function<void(c_node* item)> _click;

    std::function<void(c_node* item, BLPointI mouse)> _mouse_move;


    std::function<void(c_node* item)> _mouse_enter;
    std::function<void(c_node* item)> _mouse_leave;



    bool _force_listen_to_mouse_move = false;
    void force_listen_to_mouse_move() {_force_listen_to_mouse_move = true;}

    inline void mouse_enter(std::function<void(c_node* item)> _fn) {
        _mouse_enter = _fn;
    }
    inline void mouse_leave(std::function<void(c_node* item)> _fn) {
        _mouse_leave = _fn;
    }
    inline void mouse_move(std::function<void(c_node* item,   BLPointI mouse)> _fn, bool capture_all = false) {
        _mouse_move = _fn;
    }

    void click_listener(std::function<void(c_node* item)> _fn) {
        _click = _fn;
    }

    void transition(int ms) {

    }
};


class c_transition {
public:

    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
    std::chrono::time_point<std::chrono::high_resolution_clock> _end;

    e_transition_type type;
    bool executed = false;

    c_node* node = nullptr;


    c_transition(c_node* _node, int milliseconds) {
        this->node = _node;
        _start = std::chrono::high_resolution_clock::now();
        _end = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(milliseconds);
    }
    ~c_transition() {

    }

    virtual  void run()  =0;
};

class c_transition_margin : public c_transition {
public:

    e_edge _edge;
    float old_value = 0.f;
    float new_value = 0.f;
    c_transition_margin(c_node* node, e_edge edge, float new_value, int milliseconds)  : c_transition(node, milliseconds){
        type = e_transition_type::margin;
        this->new_value = new_value;
        auto old = YGNodeStyleGetMargin(node->node_ref, (YGEdge)_edge);

        this->old_value =  old.value > 0 ? old.value : 0;

        _edge = edge;
    }


    void run() override {

        auto elapsed_time =  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _start);


        auto elapsed = (float)elapsed_time.count();

        std::cout << "elapsed " << elapsed << std::endl;
        if (elapsed > 0) {
            auto total =  (float)std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
            auto progress =  elapsed /total;

            if (progress >= 1.f) {
                progress = 1.f;
            }

//
            auto margin = std::lerp(old_value, new_value, 1.f - std::cos((progress * 3.14f) * 0.5f));

            std::cout << "progress " << progress << std::endl;
            YGNodeStyleSetMargin(node->node_ref, (YGEdge)_edge,  margin);
            node->dirty_layout = true;

            if (progress >= 1.f)
                this->executed = true;
        }
    }
};
class  c_transitions {
public:
    c_node* node;

    std::vector<c_transition*> _transitions;
    int ms;
    c_transitions(c_node* _node) {
        node = _node;
    }


    void set_ms(int _ms) {
        ms = _ms;
    }
    //c_node* node, e_edge edge, float new_value, int millisecond
    void margin(e_edge edge, float value) {
        c_transition_margin* trans = new c_transition_margin(node,  edge, value, ms );
        _transitions.push_back(trans);
    }
};




class c_style {
private:
    BLRgba32 _background_color;
    BLRgba32 _border_color;
    BLRgba32 _color;

    float _border_stroke = 1.f;
    int _z_index = 0;

    bool _clickthrough = false;

    friend class c_node;
    friend class c_text;
public:


    c_node* node;

    c_style() {

    }
    c_style(    c_node* _node, YGNodeRef _ref) {
        node = _node;
        node_ref = _ref;
    }
    YGNodeRef node_ref;

    inline c_style& height_percent(int value) {
        YGNodeStyleSetHeightPercent(node_ref, value);
        node->mark_as_dirty();
        return *this;
    }

    inline c_style& clickthrough() {
        _clickthrough = true;
        return *this;
    }
    inline c_style&  height_auto() {
        YGNodeStyleSetHeightAuto(node_ref);
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& width_auto() {
        YGNodeStyleSetWidthAuto(node_ref);
        node->mark_as_dirty();
        return *this;
    }
    inline c_style&  height(float value) {
        YGNodeStyleSetHeight(node_ref, value);
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& color(BLRgba32 color) {
        _color = color;
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& z_index(int value) {
       _z_index = value;
        node->mark_as_dirty();
        return *this;
    }

    inline c_style& width(float value) {
        YGNodeStyleSetWidth(node_ref, value);
        node->mark_as_dirty();
        return *this;
    }

    inline c_style& margin(e_edge edge, float value) {
        YGNodeStyleSetMargin(node_ref, (YGEdge)edge, value);
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& margin_percent(e_edge edge, float value) {
        YGNodeStyleSetMarginPercent(node_ref, (YGEdge)edge, value);
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& margin_auto(e_edge edge) {
        YGNodeStyleSetMarginAuto(node_ref, (YGEdge)edge );
        node->mark_as_dirty();
        return  *this;
    }
   inline c_style&  width_percent(float value) {
        YGNodeStyleSetWidthPercent(node_ref, value);
        node->mark_as_dirty();
        return *this;
    }

    inline c_style& display(e_display display) {
        YGNodeStyleSetDisplay(node_ref, (YGDisplay)display);
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& background_color(BLRgba32 color) {
        _background_color = color;
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& border_color(BLRgba32 color) {
        node->mark_as_dirty();
        _border_color = color;
        return *this;
    }
    inline c_style& border_stroke(float value) {
        node->mark_as_dirty();
        _border_stroke = value;
        return *this;
    }

    inline c_style& gap(e_gutter gutter, float value) {
        YGNodeStyleSetGap(node_ref, (YGGutter)gutter, value);
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& flex_direction(e_flex_direction direction) {
        YGNodeStyleSetFlexDirection(node_ref, (YGFlexDirection)direction);
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& justify_content(e_justify value) {
        YGNodeStyleSetJustifyContent(node_ref, (YGJustify)value);
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& align_items(e_align value) {
        YGNodeStyleSetAlignItems(node_ref, (YGAlign)value);
        node->mark_as_dirty();
        return *this;
    }
    inline c_style& position_type(e_position position) {
      YGNodeStyleSetPositionType(node_ref, (YGPositionType)position);
        return *this;
    }
    inline c_style& position(e_edge edge, float value) {
       YGNodeStyleSetPosition(node_ref, (YGEdge)edge, value);
        return *this;
    }
    inline c_style& transition() {
        return *this;
    }


};
