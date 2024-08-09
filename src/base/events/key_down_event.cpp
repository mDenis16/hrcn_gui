#include <base/events/key_down_event.hpp>
#include <base/events/types.hpp>

c_key_down_event::c_key_down_event()
{
    type = e_node_event_type::key_down_event;
}