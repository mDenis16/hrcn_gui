#include <base/transitions/transition_border_color.hpp>
#include <base/style/style_manager.hpp>
#include <base/node.hpp>
#include <base/transitions/types.hpp>
#include <base/yg_enums.hpp>

c_transition_border_color::c_transition_border_color(c_node *_node, e_edge edge, c_color _new_color, int _milliseconds) : c_transition(_node, _milliseconds)
{
    type = e_transition_type::border_color;
    this->_edge = edge;
    this->new_color = _new_color;

   this->old_color = _node->_style->_borders.at((uint8_t)edge).color;
}
c_transition_border_color::~c_transition_border_color()
{
}

void c_transition_border_color::run()
{
    c_transition::run();

    auto &color = node->_style->_borders.at((uint8_t)_edge).color;

    if (new_color.getR() != old_color.getR())
        color.setR(std::lerp(old_color.getR(), new_color.getR(), progress));
    if (new_color.getG() != old_color.getG())
        color.setG(std::lerp(old_color.getG(), new_color.getG(), progress));
    if (new_color.getB() != old_color.getB())
        color.setB(std::lerp(old_color.getB(), new_color.getB(), progress));
    if (new_color.getA() != old_color.getA())
        color.setA(std::lerp(old_color.getA(), new_color.getA(), progress));

    node->dirty = true;
}