#include <base/transitions/transition_position.hpp>
#include <base/node.hpp>

#include <base/transitions/types.hpp>
#include <base/yg_enums.hpp>

c_transition_position::c_transition_position(c_node *node, e_edge edge, float new_value, int milliseconds) : c_transition(node, milliseconds)
{
    type = e_transition_type::position;

    this->new_value = new_value;
    auto old = YGNodeStyleGetPosition(node->node_ref, (YGEdge)edge);

    this->old_value = old.value > 0 ? old.value : 0;

    _edge = edge;
}

void c_transition_position::run()
{

    c_transition::run();
  //  std::cout << "c_transition_position << progress   " << progress << std::endl;
    auto value = std::lerp(old_value, new_value, 1.f - std::cos((progress * 3.14f) * 0.5f));

    YGNodeStyleSetPosition(node->node_ref, (YGEdge)_edge, value);
    node->mark_layout_as_dirty();
}