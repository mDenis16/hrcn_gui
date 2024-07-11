#include <base/transitions/transition_background_color.hpp>

#include <base/style/style_manager.hpp>
#include <base/node.hpp>

#include <base/transitions/types.hpp>
#include <base/yg_enums.hpp>

/// c_transition_background_color(c_node* _node,  BLRgba32 _new_color, int _milliseconds)
c_transition_background_color::c_transition_background_color(c_node *_node, BLRgba32 _new_color, int _milliseconds) : c_transition(_node, _milliseconds)
{
    type = e_transition_type::background_color;

    this->new_color = _new_color;

    this->old_color = _node->_style->_background_color;
}
c_transition_background_color::~c_transition_background_color()
{
}

void c_transition_background_color::run()
{
    // std::cout << "c_transition_position " << std::endl;
    c_transition::run();

    auto &color = node->_style->_background_color;

    if (new_color.r() != old_color.r())
        color.setR(std::lerp(old_color.r(), new_color.r(), progress));
    if (new_color.g() != old_color.g())
        color.setG(std::lerp(old_color.g(), new_color.g(), progress));
    if (new_color.b() != old_color.b())
        color.setB(std::lerp(old_color.b(), new_color.b(), progress));
    if (new_color.a() != old_color.a())
        color.setB(std::lerp(old_color.a(), new_color.a(), progress));



    node->dirty = true;
}