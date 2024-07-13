#pragma once
#include <blend2d.h>
/*
onclick	The user clicks on an element
oncontextmenu	The user right-clicks on an element
ondblclick	The user double-clicks on an element
onmousedown	A mouse button is pressed over an element
onmouseenter	The pointer is moved onto an element
onmouseleave	The pointer is moved out of an element
onmousemove	The pointer is moving over an element
onmouseout	The mouse pointer moves out of an element
onmouseover	The mouse pointer is moved over an element
onmouseup

 **/

class c_node;
enum class e_node_event_type : unsigned char;

class c_node_event
{
public:
    e_node_event_type type;
    c_node *target;

    BLPoint position;



    ~c_node_event()
    {
    }
    c_node_event()
    {
    }
    c_node_event(c_node *_target, e_node_event_type _type) : type(_type), target(_target){

    }


    
    bool _stop_propagation = false;

    void stop_propagation(){
        _stop_propagation= true;
    }
    template <typename T>
    T *as()
    {
        return (T *)(this);
    }
};