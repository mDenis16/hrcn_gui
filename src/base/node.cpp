
#include <base/app_context.hpp>
#include "node.hpp"

#include "mouse_event.hpp"

#include <iostream>
#include <sstream>
#include "transitions/transition.hpp"
#include <base/transitions/transitions_manager.hpp>
#include <base/style/style_manager.hpp>
#include <base/event_listener.hpp>
#include <base/events/types.hpp>

#include <base/effect.hpp>
#include <base/state.hpp>
#include <mutex>
#include <base/yg_enums.hpp>
#include <algorithm>
#include <base/app_context.hpp>
#include <utils/path_generator.hpp>

#include "font.hpp"
#include "blend2d/pipeline/pipedefs_p.h"
#include "events/mouse_scroll_event.hpp"


static int idx = 0;
c_node::c_node(/* args */)
{
    node_ref = (c_node_ref*)YGNodeNew();


    _style = new c_style_manager(this);
    _transitions = new c_transitions_manager(this);
    _pending = new c_pending_state(this);


    //   YGNodeStyleSetPositionType(node_ref, YGPositionTypeRelative);
    YGNodeSetAlwaysFormsContainingBlock((YGNodeRef)node_ref, true /*alwaysFormsContainingBlock*/);
};

void c_node::safe_destroy()
{
    this->parent->remove_child(this);
    this->destroy();
}
void c_node::clear()
{

    if (app_context == nullptr)
    {
        std::cout << "c_node::clear() app_context is null " << std::endl;
        return;
    }
    for (unsigned int i = 0; i < children.size(); i++)
        children[i]->destroy();

    children.clear();
}

void c_node::destroy()
{


    if (app_context == nullptr)
    {
        std::cout << "c_node::destroy() app_context is null " << std::endl;
        return;
    }

    std::cout << "app_context " << app_context << std::endl;

    app_context->remove_event_listeners_for_node(this);

    std::cout << "c_node destroy [is_text] " << is_text << std::endl;

    for (unsigned int i = 0; i < children.size(); i++)
        children[i]->destroy();

    // if (parent)
    ///   parent->remove_child(his);

    app_context->remove_node(this);

    YGNodeFree((YGNodeRef)node_ref);

    children.clear();

    app_context->remove_transitions_for_node(this);

    std::cout << "nodes.size() " << c_app_context::get_current()->_nodes.size() << std::endl;

    delete this;
}
c_node::~c_node()
{
    delete _transitions;
    delete _style;
}

void c_node::use_state(c_state *state)
{
    _states.push_back((c_state *)state);
}
void c_node::use_effect(std::function<void()> _callback, std::vector<c_state *> _states)
{

    auto effect = new c_effect(this, _callback, _states);

    _pending->add_effect(this, effect);
    for (auto &state : _states) {
        state->_effects.push_back(effect);
        _pending->add_state(state);
    }

}

void c_node::sync_context() {



}
void c_node::check_for_state_changes()
{
}

void c_pending_state::add_event_listener(c_node *node, c_event_listener *listener) {
    _event_listeners.push_back(listener);
}
void c_pending_state::add_effect(c_node* node, c_effect* effect) {
    this->_effects.push_back(effect);
}
void c_pending_state::add_state(c_state* state) {
    this->_states.push_back(state);
}
c_event_listener *c_node::add_event_listener(e_node_event_type type, std::function<void(c_node_event *)> _fn)
{
    c_event_listener *listener = new c_event_listener(type, this, _fn);


    if (app_context)
        app_context->add_event_listener(this, listener);
    else
        _pending->add_event_listener(this, listener);
    return listener;
}
void c_node::remove_event_listener(c_event_listener *_event_listener)
{
    c_app_context::get_current()->remove_event_listener(_event_listener);
}

float deg2rad(float degrees) {
    double radians = degrees * (M_PI / 180.0);
    return  radians;
}

bool c_node::have_rounded_borders() {
    for(auto& border : _style->_border_corners)
        if (border.radius > 0.f)
            return true;

   return  false;
}
BLImage tampenie(int w, int h) {


    // create the main BLContext
    BLImage img(w, h, BL_FORMAT_PRGB32);
    BLContext ctx(img);
    ctx.clearAll();
    ctx.setFillStyle(BLRgba32(0,255,255,100));
    ctx.fillRect(BLRect(0,0, w, h));
    ctx.setTransform( {1,0,0,1, w * 0.5,h * 0.5} ); //put the origin at the center of img


    ctx.fillCircle(0,0,90);
    ctx.setFillStyle(BLRgba32(255,0,0,255));
    ctx.fillTriangle(-w * 0.5,-h * 0.5, 0, 0, -w * 0.5, h * 0.5 );
    ctx.setFillStyle(BLRgba32(0,255,0,255));
    ctx.fillTriangle(w * 0.5,-h * 0.5, 0, 0, w * 0.5, h * 0.5);
    ctx.setFillStyle(BLRgba32(0,0,255,255));
    ctx.fillTriangle(-w * 0.5,-h * 0.5, 0, 0, w * 0.5, -h * 0.5 );

    ctx.fillTriangle(-w * 0.5,h * 0.5, 0, 0, w * 0.5, h * 0.5 );
    ctx.end();

    return img;
}
double distanceBetweenTwoPoints( BLPoint a, BLPoint b)  {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return std::sqrt(dx * dx + dy * dy);
}
float angleBetweenTwoPoints(BLPoint a, BLPoint b) {
  BLPoint dif = a - b;

    float theta = std::atan2f(dif.y, dif.x); // range (-PI, PI]
    return theta;
}
BLPoint generatePoint(BLPoint base,float angle, float distance) {
    double newX = base.x + distance * std::cos(angle);
    double newY = base.y + distance * std::sin(angle);

    return BLPoint(newX,newY);
}
void c_node::render(BLContext &context) {
    if (parent && YGNodeLayoutGetHadOverflow((YGNodeRef)parent->node_ref))
    {
        auto parent_box = parent->box;
        if ((box.y > parent_box.y + parent_box.h) || box.y + box.h < parent_box.y)
            return;
    }
    bool restore_clipping = false;

    context.setFillStyle(BLRgba32(_style->_background_color.getR(),_style->_background_color.getG(),_style->_background_color.getB(),_style->_background_color.getA()));
    context.fillRect(BLRectI((int)box.x, (int)box.y, (int)box.w, (int)box.h));

    if (overflow_y && _style->_overflow_hidden)
        context.clipToRect(box);

    for (auto &child : children) {
        if (child->style().get_z_index() == 0)
            child->render(context);
    }

    if (overflow_y && _style->_overflow_hidden)
        context.restoreClipping();

    auto& border_top = _style->_borders.at((uint8_t)e_edge::top);
    auto& border_bottom = _style->_borders.at((uint8_t)e_edge::bottom);
    auto& border_left =  _style->_borders.at((uint8_t)e_edge::left);
    auto& border_right =  _style->_borders.at((uint8_t)e_edge::right);

    context.setFillStyle(BLRgba32(border_top.color.getR(), border_top.color.getG(), border_top.color.getB(), border_top.color.getA()));
    context.fillRect(BLRectI(box.x, box.y, box.w, border_top.value));

    context.setFillStyle(BLRgba32(border_bottom.color.getR(), border_bottom.color.getG(), border_bottom.color.getB(), border_bottom.color.getA()));
    context.fillRect(BLRectI(box.x, box.y, border_bottom.value, box.h));

    context.setFillStyle(BLRgba32(border_left.color.getR(), border_left.color.getG(), border_left.color.getB(), border_left.color.getA()));
    context.fillRect(BLRectI(box.x + box.w - border_left.value, box.y, border_left.value, box.h));

    context.setFillStyle(BLRgba32(border_right.color.getR(), border_right.color.getG(), border_right.color.getB(), border_right.color.getA()));

    context.fillRect(BLRectI(box.x, box.y + box.h - border_right.value, box.w, border_right.value));

    dirty = false;
}
bool c_node::absolute_anchestor(int &z_index)
{
    c_node *current = this;

    int highest = 0;
    while (current != nullptr)
    {
        if (current->absolute)
        {
            if (current->_style->get_z_index() >= highest)
            {
                z_index = current->_style->get_z_index();
                highest = z_index;
            }
            return true;
        }
        current = current->parent;
    }

    return false;
}

void c_node::layout_update(BLPointI point)
{
    std::cout << "c_node::layout_update " << std::endl;
    if (!node_ref)
        return;

    if (parent && app_context == nullptr)
        app_context = parent->app_context;

    if (app_context == nullptr) {
        assert("App context is null in layout update.");
        return;
    }



    if (app_context) {
        if (!_pending->is_consumed())
            _pending->consume();
    }


    const auto layout_width =  YGNodeLayoutGetWidth((YGNodeRef)node_ref);
    const auto layout_height = YGNodeLayoutGetHeight((YGNodeRef)node_ref);

    box.x = point.x + YGNodeLayoutGetLeft((YGNodeRef)node_ref);
    box.y = point.y + YGNodeLayoutGetTop((YGNodeRef)node_ref);
    box.w = layout_width;
    box.h = layout_width;


    static_box = box;



    for (auto &child : children)
        child->layout_update(BLPointI(box.x, box.y - scroll * (content_box.h)));



    content_box = calculate_bounding_box_of_children();

    // content_box.h = content_size().h;

    overflow_y = content_box.h > box.h;

    max_scroll = (box.h) / (content_box.h);
    dirty_layout = false;

    if (!this->scroll_listener && overflow_y)
        this->scroll_listener = this->add_event_listener(e_node_event_type::mouse_scroll_event, [this](c_node_event *event)
                                                         {
                                                             if (!overflow_y)
                                                                 return;
                                                             event->stop_propagation();
                                                             std::cout << " on scroll " << std::endl;
                                                             auto scroll_event = event->as<c_mouse_scroll_event>();
                                                             auto offset = abs(scroll_event->offset.y);

                                                             if (scroll_event->offset.y < 0)
                                                                 scroll += 0.03f * offset;
                                                             else if (scroll_event->offset.y > 0)
                                                                 scroll -= 0.03f * offset;

                                                             std::cout << "max_scroll " << max_scroll << std::endl;
                                                             scroll = std::clamp(scroll, 0.f, 1.f - max_scroll);

                                                             std::cout << " scroll " << scroll << std::endl;
                                                             mark_layout_as_dirty();
                                                         });


}

BLRect c_node::calculate_bounding_box_of_children()
{
    if (children.empty())
    {
        return BLRect{0, 0, 0, 0}; // No children, return an empty box
    }

    // Initialize with the first child's bounding box
    auto first_child_box = children.front()->calc_total_size();
    double min_x = first_child_box.x;
    double min_y = first_child_box.y;
    double max_x = first_child_box.x + first_child_box.w;
    double max_y = first_child_box.y + first_child_box.h;

    // Iterate over all children and adjust the bounding box
    for (const auto &child : children)
    {
        if (child->style().get_position() == e_position::position_type_absolute)
            continue;

        auto child_box = child->calc_total_size();
        if (child_box.x < min_x)
            min_x = child_box.x;
        if (child_box.y < min_y)
            min_y = child_box.y;
        if (child_box.x + child_box.w > max_x)
            max_x = child_box.x + child_box.w;
        if (child_box.y + child_box.h > max_y)
            max_y = child_box.y + child_box.h;
    }

    // Return the calculated bounding box
    return BLRect{min_x, min_y, max_x - min_x, max_y - min_y};
}

BLSize c_node::content_size()
{
    if (children.empty())
        return BLSize{0.f, 0.f};
    if (children.size() < 2)
    {
        auto size = children.back()->calc_total_size();
        return BLSize{size.w, size.h};
    }

    auto front = children.front()->calc_total_size();
    auto back = children.back()->calc_total_size();

    return BLSize{back.x + back.w - front.x, back.y + back.h - front.y};
}

void c_node::add_child(c_node *node)
{
    YGNodeInsertChild((YGNodeRef)node_ref, (YGNodeRef)node->node_ref, children.size());
    node->parent = this;
    node->child_index = children.size();

    children.push_back(node);

    mark_layout_as_dirty();

    c_node* current = this;

    while (current != nullptr) {
        if (current->is_root)
            current->propagate_context(current->app_context);

        current = current->parent;
    }

}
void c_node::remove_child(c_node *node)
{

    children.erase(std::remove_if(children.begin(), children.end(),
                                  [node](c_node *c)
                                  { return c == node; }),
                   children.end());

    mark_layout_as_dirty();
}


void c_node::propagate_context(c_app_context* context)
{

    if (is_root)
        app_context->_nodes.clear();


    app_context = context;


    app_context->_nodes.push_back(this);



    assert(context);

    for (auto &child : children)
        child->propagate_context(context);



    if (is_root)
        std::reverse(app_context->_nodes.begin(), app_context->_nodes.end());

    if (app_context && !_init && _on_init) {
        _on_init();
        _init = true;
    }
}
void c_node::handle_event(c_node_event *event)
{
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

void c_node::on_event(c_node_event *event)
{
}

// void c_node::update_transitions()
// {

//     for (auto &transition : _transitions->_list)
//     {

//         transition->run();

//         if (transition->executed)
//         {

//             auto itx = std::find(_transitions->_list.begin(), _transitions->_list.end(), transition);
//             if (itx != _transitions->_list.end())
//                 _transitions->_list.erase(itx);
//         }
//     }
//     for (auto &node : children)
//         node->update_transitions();
// }

bool c_node::require_rerender(bool &_dirty_layout)
{

    auto d = this;
    bool drty = false;


    for (c_node *node : app_context->_nodes)
    {

        if (node->dirty || node->dirty_layout)
        {
            if (node->dirty_layout)
                _dirty_layout = true;

            drty = true;
        }
    }
    return drty;
}

BLRect c_node::calc_total_size()
{
    if (node_ref == nullptr)
        return BLRect{};

    if (style().get_position() == e_position::position_type_absolute)
        return BLRect{};

    BLRect original = box;

    original.w += YGNodeLayoutGetMargin((YGNodeRef)node_ref, YGEdgeLeft) + YGNodeLayoutGetMargin((YGNodeRef)node_ref, YGEdgeRight);
    original.h += YGNodeLayoutGetMargin((YGNodeRef)node_ref, YGEdgeTop) + YGNodeLayoutGetMargin((YGNodeRef)node_ref, YGEdgeBottom) +
                  YGNodeLayoutGetPadding((YGNodeRef)node_ref, YGEdgeTop) + YGNodeLayoutGetPadding((YGNodeRef)node_ref, YGEdgeBottom);

    return original;
}

c_transitions_manager &c_node::transitions(int ms)
{
    _transitions->milliseconds = ms;
    return *_transitions;
}
void c_pending_state::consume() {

    for (auto event_listener : _event_listeners)
        _node->app_context->add_event_listener(_node, event_listener);

    for(auto state : _states)
        _node->app_context->add_state(state);

    _node->app_context->add_node(_node);

    _states.clear();
    _event_listeners.clear();
    _consumed = true;
}

