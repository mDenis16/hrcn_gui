#pragma once
class c_node;
class c_effect;
#include <vector>
class c_state
{
public:
    c_node *node;
    std::vector<c_effect*> _effects;
    c_state();
    ~c_state();

    bool _update = false;


    inline void update()
    {
        _update = true;
    }

    virtual bool require_update()
    {
        return _update;
    }

    void consume_update();
    
};