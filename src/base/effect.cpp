#include <base/effect.hpp>
#include <base/node.hpp>
#include <base/state.hpp>

c_effect::c_effect(c_node *_node, std::function<void()> _callback, std::vector<c_state *> &_states) : node(_node), callback(_callback), states(std::move(_states))
{
    for (auto &state : states)
    {
        state->node = _node;
        state->effect = this;
    }
}
c_effect::~c_effect()
{
}