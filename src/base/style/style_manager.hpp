#pragma once
#include <Yoga/Yoga.h>
#include <blend2d.h>
/*
YOGA ABSTRACTION
*/

enum class e_edge : uint8_t;
enum class e_position : uint8_t;
enum class e_align : uint8_t;
enum class e_justify : uint8_t;
enum class e_flex_direction : uint8_t;
enum class e_display : uint8_t;
enum class e_gutter : uint8_t;
enum class e_wrap : uint8_t;

class c_node;

class c_style_manager
{
private:
    BLRgba32 _background_color;
    BLRgba32 _border_color;
    BLRgba32 _color;

    bool _overflow_hidden = false;

    float _border_stroke = 1.f;
    int _z_index = 0;

    bool _clickthrough = false;

    friend class c_node;
    friend class c_text;
    friend class c_transition_background_color;
    friend class c_transition_border_color;
public:
    c_node *node;

    int get_z_index() {
        return _z_index;
    }
    c_style_manager()
    {
    }
    c_style_manager(c_node *_node, YGNodeRef _ref)
    {
        node = _node;
        node_ref = _ref;
    }
    YGNodeRef node_ref;

    c_style_manager &set_flex_wrap(e_wrap value);
    c_style_manager &set_flex_basis(float value) ;
    c_style_manager &set_flex_grow(float value);
    c_style_manager &set_flex_shrink(float value);
    c_style_manager &height_percent(int value);

    c_style_manager &clickthrough();

    c_style_manager &overflow_hidden();

    c_style_manager &height_auto();
    c_style_manager &width_auto();
    c_style_manager &height(float value);
    c_style_manager &color(BLRgba32 color);
    c_style_manager &z_index(int value);
    c_style_manager &width(float value);

    c_style_manager &margin(e_edge edge, float value);
    c_style_manager &margin_percent(e_edge edge, float value);
    c_style_manager &margin_auto(e_edge edge);
    c_style_manager &width_percent(float value);

    c_style_manager &display(e_display display);
    c_style_manager &background_color(BLRgba32 color);
    c_style_manager &border_color(BLRgba32 color);
    c_style_manager &border_stroke(float value);
    c_style_manager &padding(e_edge edge, float value);


    c_style_manager &gap(e_gutter gutter, float value);
    c_style_manager &flex_direction(e_flex_direction direction);
    c_style_manager &justify_content(e_justify value);
    c_style_manager &align_items(e_align value);
    c_style_manager &position_type(e_position position);
    c_style_manager &position(e_edge edge, float value);
    c_style_manager &transition();
};
