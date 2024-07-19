#include "transition.hpp"

c_transition::c_transition(c_node *_node, int milliseconds)
{
    std::cout << " c_transition with ms " << milliseconds << std::endl;
    this->node = _node;
    _start = std::chrono::high_resolution_clock::now();
    _end = _start + std::chrono::milliseconds(milliseconds);
}

void c_transition::run()
{
    if (executed)
        return;
    _has_run = false;

    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _start);

    auto elapsed = (float)elapsed_time.count();

   
    if (elapsed > 0)
    {
        auto total = (float)std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
        progress = elapsed / total;

        if (progress >= 1.f)
        {
           // std::cout << "finished executing it " << std::endl;
            progress = 1.f;
            executed = true;
            return;
        }
    }
    _has_run = true;
}