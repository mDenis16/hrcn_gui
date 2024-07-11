#pragma once
class c_node;
class c_effect;

class c_state
{
public:
    c_node *node;
    c_effect* effect;
    c_state();
    ~c_state();

    bool _update = false;

    void update()
    {
        _update = true;
    }

    bool require_update()
    {
        return _update;
    }

    void consume_update();
    
};