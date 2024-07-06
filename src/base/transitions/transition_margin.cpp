#include <base/transitions/transition_margin.hpp>
#include <base/node.hpp>

#include <base/transitions/types.hpp>
#include <base/yg_enums.hpp>

c_transition_margin::c_transition_margin(c_node *node, e_edge edge, float new_value, int milliseconds) : c_transition(node, milliseconds)
{
        // type = e_transition_type::margin;
        // this->new_value = new_value;
        // auto old = YGNodeStyleGetMargin(node->node_ref, (YGEdge)edge);

        // this->old_value =  old.value > 0 ? old.value : 0;

        // _edge = edge;
}

void c_transition_margin::run()
{
        // auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _start);

        // auto elapsed = (float)elapsed_time.count();

        // std::cout << "elapsed " << elapsed << std::endl;
        // if (elapsed > 0)
        // {
        //         auto total = (float)std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
        //         auto progress = elapsed / total;

        //         if (progress >= 1.f)
        //         {
        //                 progress = 1.f;
        //         }

        //         //
        //         auto margin = std::lerp(old_value, new_value, 1.f - std::cos((progress * 3.14f) * 0.5f));

        //         std::cout << "progress " << progress << std::endl;
        //         YGNodeStyleSetMargin(node->node_ref, (YGEdge)_edge, margin);
        //         node->dirty_layout = true;

        //         if (progress >= 1.f)
        //                 this->executed = true;
        // }
}