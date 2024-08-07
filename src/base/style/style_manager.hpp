#pragma once
#include <Yoga/Yoga.h>
#include <blend2d.h>

#include <base/style/color.hpp>
#include <array>
#include <base/yg_enums.hpp>

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
enum class e_corner : uint8_t;

class c_node;


enum class e_border_type {
    aa_stroke,
    line
};


class c_border {
public:
    c_border(){};
    ~c_border(){};
    e_border_type type = e_border_type::aa_stroke;
    c_color color = c_color(0,0,0,0);
    float value = 0.f;
};

class c_border_corner {
public:
    c_border_corner(){};
    ~c_border_corner(){};

    float radius = 0.f;
};
class c_style_manager
{
private:
    c_color _background_color;
    c_color _color;

    std::array<c_border, 4> _borders;
    std::array<c_border_corner, 4> _border_corners;

    e_position _position = e_position::position_type_relative;

    bool _overflow_hidden = false;
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

    e_position get_position() {
        return _position;
    }

    c_style_manager(c_node *_node)
    {
        node = _node;

    }
    

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
    c_style_manager &color(c_color color);
    c_style_manager &z_index(int value);
    c_style_manager &width(float value);

    c_style_manager &margin(e_edge edge, float value);
    c_style_manager &margin_percent(e_edge edge, float value);
    c_style_manager &margin_auto(e_edge edge);
    c_style_manager &width_percent(float value);

    c_style_manager &display(e_display display);
    c_style_manager &background_color(c_color color);
    c_style_manager &border_color(e_edge edge, c_color color);


    c_style_manager &border_color(c_color color);

    c_style_manager &border_radius(float value);

    c_style_manager &border_width(float value);
    c_style_manager &border_width(e_edge edge, float value);

    c_style_manager &border_line(e_edge edge,float value);

    c_style_manager &border_stroke(float value);

    c_style_manager &border_radius(e_corner edge,float value);
    c_style_manager &padding(e_edge edge, float value);


    c_style_manager &gap(e_gutter gutter, float value);
    c_style_manager &flex_direction(e_flex_direction direction);
    c_style_manager &justify_content(e_justify value);
    c_style_manager &align_items(e_align value);
    c_style_manager &position_type(e_position position);
    c_style_manager &position(e_edge edge, float value);
    c_style_manager &transition();
};
