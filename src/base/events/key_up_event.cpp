#include <base/events/key_up_event.hpp>
#include <base/events/types.hpp>

c_key_up_event::c_key_up_event()
{
    type = e_node_event_type::key_up_event;
}