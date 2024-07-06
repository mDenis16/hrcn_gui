#include "node.hpp"

#include "mouse_event.hpp"

#include <iostream>

#include "scroll_event.hpp"


c_node::c_node(/* args */) {
    node_ref = YGNodeNew();
    bg_color = BLRgba32(0, 255, 0, 100);
    border_color = BLRgba32(255, 255, 0, 0);

    _style = new c_style(this, node_ref);
    _transitions = new c_transitions(this);

    nodes.push_back(this);
    YGNodeStyleSetPositionType(node_ref, YGPositionTypeRelative);
    YGNodeSetAlwaysFormsContainingBlock(node_ref, true /*alwaysFormsContainingBlock*/);
};

c_node::~c_node() {
}


void c_node::render(BLContext &context) {
    //if (overflow_y)
    //  context.clipToRect(box);

    context.setFillStyle(_style->_background_color);
    context.fillRect(BLRectI((int)box.x, (int)box.y, (int)box.w, (int)box.h));


    for (auto &child: children)
        child->render(context);

    context.setFillStyle(_style->_border_color);
    context.fillRect(BLRectI(box.x, box.y, box.w, 1));
    context.fillRect(BLRectI(box.x, box.y, 1, box.h));

    context.fillRect(BLRectI(box.x + box.w - 1, box.y , 1, box.h));

    context.fillRect(BLRectI(box.x, box.y + box.h - 1, box.w, 1));
   // context.strokeRect(BLRectI((int)box.x, (int)box.y, (int)box.w, (int)box.h));


    //context.strokeRect(static_box);


    //  if (overflow_y)
    //        context.restoreClipping();

    dirty = false;
}

void c_node::layout_update(BLPointI point) {
    box.x = point.x + YGNodeLayoutGetLeft(node_ref);
    box.y = point.y + YGNodeLayoutGetTop(node_ref);
    box.w = YGNodeLayoutGetWidth(node_ref);
    box.h = YGNodeLayoutGetHeight(node_ref);


    static_box = box;

    biggest_z_index = z_index;




    for (auto &child: children) {
        child->layout_update(BLPointI(box.x, box.y));
    }


    content_box = calculate_bounding_box_of_children();

    // content_box.h = content_size().h;

    overflow_y = content_box.h > box.h;

    max_scroll = (box.h) / (content_box.h);
}

BLRect c_node::calculate_bounding_box_of_children() {
    if (children.empty()) {
        return BLRect{0, 0, 0, 0}; // No children, return an empty box
    }

    // Initialize with the first child's bounding box
    auto first_child_box = children.front()->calc_total_size();
    double min_x = first_child_box.x;
    double min_y = first_child_box.y;
    double max_x = first_child_box.x + first_child_box.w;
    double max_y = first_child_box.y + first_child_box.h;

    // Iterate over all children and adjust the bounding box
    for (const auto &child: children) {
        auto child_box = child->calc_total_size();
        if (child_box.x < min_x) min_x = child_box.x;
        if (child_box.y < min_y) min_y = child_box.y;
        if (child_box.x + child_box.w > max_x) max_x = child_box.x + child_box.w;
        if (child_box.y + child_box.h > max_y) max_y = child_box.y + child_box.h;
    }

    // Return the calculated bounding box
    return BLRect{min_x, min_y, max_x - min_x, max_y - min_y};
}

BLSize c_node::content_size() {
    if (children.empty())
        return BLSize{0.f, 0.f};
    if (children.size() < 2) {
        auto size = children.back()->calc_total_size();
        return BLSize{size.w, size.h};
    }

    auto front = children.front()->calc_total_size();
    auto back = children.back()->calc_total_size();

    return BLSize{back.x + back.w - front.x, back.y + back.h - front.y};
}

void c_node::add_child(c_node *node) {
    YGNodeInsertChild(node_ref, node->node_ref, children.size());
    node->parent = this;
    node->child_index =children.size();
    children.push_back(node);
}

void c_node::handle_event(c_node_event *event) {
 /*   if (event->ev_type == e_event_type::mouse) {
        c_mouse_event *ev = (c_mouse_event *) event;
        if (!(ev->position.x >= box.x && ev->position.x <= box.x + box.w && ev->position.y >= box.y && ev->position.y <= box.y + box.h))
            return;

        if (ev->consumed) return;

        for (auto &child: children)
            child->handle_event(event);


        if (  _click &&  ev->mouse_event_type == e_mouse_event_type::onclick) {
            _click(this);
            ev->consumed = true;
        }
        if (  _click &&  ev->mouse_event_type == e_mouse_event_type::onmousemove) {
            _mouse_move(this, ev->position);
        }


        on_event(event);
    }
    else
    if (event->ev_type == e_event_type::scroll && overflow_y) {
        const auto scroll_event = event->as<c_scroll_event>();

        event->stop_propagation();


        auto offset = abs(scroll_event->offset.y);

        if (scroll_event->offset.y < 0)
            scroll += 0.003f * offset;
        else if (scroll_event->offset.y > 0)
            scroll -= 0.003f * offset;


        std::cout << "max_scroll " << max_scroll << std::endl;
        scroll = std::clamp(scroll, 0.f, 1.f - max_scroll);

        std::cout << " scroll " << scroll << std::endl;
        for (auto &child: children)
            child->layout_update(BLPointI(box.x, box.y - scroll * (content_box.h)));

        content_box = calculate_bounding_box_of_children();

        mark_as_dirty();

        on_event(event);
    }*/
}


void c_node::on_event(c_node_event *event) {

}

bool c_node::require_rerender() {
    auto d = this;
    bool drty = false;
    for (auto &node: nodes) {

        if (node->_transitions) {
            if (node->_transitions->_transitions.size()) {
                for(auto& trans :   node->_transitions->_transitions) {
                    if (!trans->executed) {
                        trans->run();
                        d->dirty_layout = true;
                        d->dirty = true;
                        node->dirty = true;
                        drty = true;
                    }
                }
            }
        }
        if (node->dirty && node->is_root) {
            assert(node->parent == nullptr  &&  "Dirty node without parent, unable to update.");
            drty = true;
        }

    }
    return drty;
}


BLRect c_node::calc_total_size() {
    BLRect original = box;

    original.w += YGNodeLayoutGetMargin(node_ref, YGEdgeLeft) + YGNodeLayoutGetMargin(node_ref, YGEdgeRight);
    original.h += YGNodeLayoutGetMargin(node_ref, YGEdgeTop) + YGNodeLayoutGetMargin(node_ref, YGEdgeBottom) +
            YGNodeLayoutGetPadding(node_ref, YGEdgeTop) + YGNodeLayoutGetPadding(node_ref, YGEdgeBottom);

    return original;
}

c_transitions& c_node::transitions(int ms) {
    _transitions->set_ms(ms);
    return *_transitions;
}

