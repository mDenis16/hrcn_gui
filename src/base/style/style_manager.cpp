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


c_style_manager &c_style_manager::set_flex_grow(float value) {
    YGNodeStyleSetFlexGrow((YGNodeRef)node->getRef(), value);
    node->mark_layout_as_dirty();
    return *this;
}

c_style_manager &c_style_manager::set_flex_shrink(float value) {
    YGNodeStyleSetFlexShrink((YGNodeRef)node->getRef(), value);
    node->mark_layout_as_dirty();
    return *this;
}

c_style_manager &c_style_manager::set_flex_basis(float value) {
    YGNodeStyleSetFlexBasis((YGNodeRef)node->getRef(), value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::set_flex_wrap(e_wrap value) {
    YGNodeStyleSetFlexWrap((YGNodeRef)node->getRef(), (YGWrap)value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::overflow_hidden() {
    _overflow_hidden = true;
    node->mark_layout_as_dirty();
    return *this;
}

c_style_manager &c_style_manager::height_auto()
{
    YGNodeStyleSetHeightAuto((YGNodeRef)node->getRef());

    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::width_auto()
{
    YGNodeStyleSetWidthAuto((YGNodeRef)node->getRef());
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::height(float value)
{
    YGNodeStyleSetHeight((YGNodeRef)node->getRef(), value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::height_percent(int value)
{
    YGNodeStyleSetHeightPercent((YGNodeRef)node->getRef(), value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::color(c_color color)
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
    YGNodeStyleSetWidth((YGNodeRef)node->getRef(), value);
    node->mark_layout_as_dirty();
    return *this;
}

c_style_manager &c_style_manager::padding(e_edge edge, float value)
{
    YGNodeStyleSetPadding((YGNodeRef)node->getRef(), (YGEdge)edge, value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::margin(e_edge edge, float value)
{
    YGNodeStyleSetMargin((YGNodeRef)node->getRef(), (YGEdge)edge, value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::margin_percent(e_edge edge, float value)
{
    YGNodeStyleSetMarginPercent((YGNodeRef)node->getRef(), (YGEdge)edge, value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::margin_auto(e_edge edge)
{
    YGNodeStyleSetMarginAuto((YGNodeRef)node->getRef(), (YGEdge)edge);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::width_percent(float value)
{
    YGNodeStyleSetWidthPercent((YGNodeRef)node->getRef(), value);
    node->mark_layout_as_dirty();
    return *this;
}

c_style_manager &c_style_manager::display(e_display display)
{
    YGNodeStyleSetDisplay((YGNodeRef)node->getRef(), (YGDisplay)display);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::background_color(c_color color)
{
    _background_color = color;
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::border_color(c_color color)
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
    YGNodeStyleSetGap((YGNodeRef)node->getRef(), (YGGutter)gutter, value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::flex_direction(e_flex_direction direction)
{
    YGNodeStyleSetFlexDirection((YGNodeRef)node->getRef(), (YGFlexDirection)direction);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::justify_content(e_justify value)
{
    YGNodeStyleSetJustifyContent((YGNodeRef)node->getRef(), (YGJustify)value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::align_items(e_align value)
{
    YGNodeStyleSetAlignItems((YGNodeRef)node->getRef(), (YGAlign)value);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::position_type(e_position position)
{
    _position = position;

    YGNodeStyleSetPositionType((YGNodeRef)node->getRef(), (YGPositionType)position);
    node->mark_layout_as_dirty();
    return *this;
}
c_style_manager &c_style_manager::position(e_edge edge, float value)
{
    YGNodeStyleSetPosition((YGNodeRef)node->getRef(), (YGEdge)edge, value);
    node->mark_layout_as_dirty();
    return *this;
}
