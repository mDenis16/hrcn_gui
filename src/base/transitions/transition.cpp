#include "transition.hpp"

c_transition::c_transition(c_node *_node, int milliseconds)
{
    this->node = _node;
    _start = std::chrono::high_resolution_clock::now();
    _end = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(milliseconds);
}