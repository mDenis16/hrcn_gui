#include <base/effect.hpp>
#include <base/node.hpp>
#include <base/state.hpp>

c_effect::c_effect(c_node *_node, std::function<void()> _callback, std::vector<c_state *> _states) : node(_node), callback(_callback), states(_states)
{
}
c_effect::~c_effect()
{
}