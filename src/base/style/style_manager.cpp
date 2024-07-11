#include "style_manager.hpp"

#include <base/style/style_manager.hpp>

#include <base/yg_enums.hpp>
#include <base/node.hpp>
#include <yoga/Yoga.h>

c_style_manager &c_style_manager::clickthrough()
{
    _clickthrough = true;
    return *this;
}
c_style_manager &c_style_manager::height_auto()
{
    YGNodeStyleSetHeightAuto(node_ref);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::width_auto()
{
    YGNodeStyleSetWidthAuto(node_ref);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::height(float value)
{
    YGNodeStyleSetHeight(node_ref, value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::height_percent(int value)
{
    YGNodeStyleSetHeightPercent(node_ref, value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::color(BLRgba32 color)
{
    _color = color;
    node->mark_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::z_index(int value)
{
    _z_index = value;
    node->mark_layout_as_dirty();
    return *this;
}

c_style_manager &c_style_manager::width(float value)
{
    YGNodeStyleSetWidth(node_ref, value);
    node->mark_layout_as_dirty();
    return *this;
}

c_style_manager &c_style_manager::padding(e_edge edge, float value)
{
    YGNodeStyleSetPadding(node_ref, (YGEdge)edge, value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::margin(e_edge edge, float value)
{
    YGNodeStyleSetMargin(node_ref, (YGEdge)edge, value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::margin_percent(e_edge edge, float value)
{
    YGNodeStyleSetMarginPercent(node_ref, (YGEdge)edge, value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::margin_auto(e_edge edge)
{
    YGNodeStyleSetMarginAuto(node_ref, (YGEdge)edge);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::width_percent(float value)
{
    YGNodeStyleSetWidthPercent(node_ref, value);
    node->mark_layout_as_dirty();
    return *this;
}

c_style_manager &c_style_manager::display(e_display display)
{
    YGNodeStyleSetDisplay(node_ref, (YGDisplay)display);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::background_color(BLRgba32 color)
{
    _background_color = color;
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::border_color(BLRgba32 color)
{
    node->mark_layout_as_dirty();
    _border_color = color;
    return *this;
}
c_style_manager &c_style_manager::border_stroke(float value)
{
    node->mark_layout_as_dirty();
    _border_stroke = value;
    return *this;
}

c_style_manager &c_style_manager::gap(e_gutter gutter, float value)
{
    YGNodeStyleSetGap(node_ref, (YGGutter)gutter, value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::flex_direction(e_flex_direction direction)
{
    YGNodeStyleSetFlexDirection(node_ref, (YGFlexDirection)direction);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::justify_content(e_justify value)
{
    YGNodeStyleSetJustifyContent(node_ref, (YGJustify)value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::align_items(e_align value)
{
    YGNodeStyleSetAlignItems(node_ref, (YGAlign)value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::position_type(e_position position)
{
    YGNodeStyleSetPositionType(node_ref, (YGPositionType)position);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::position(e_edge edge, float value)
{
    YGNodeStyleSetPosition(node_ref, (YGEdge)edge, value);
    node->mark_layout_as_dirty();
    return *this;
}
