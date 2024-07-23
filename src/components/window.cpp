#include <base/style/style_manager.hpp>

#include "../base/node.hpp"
#include "window.hpp"

#include <fstream>
#include <algorithm>
#include <Windows.h>

c_window::c_window(BLSizeI size)
{
    is_root = true;
    texture = BLImage(size.w, size.h, BL_FORMAT_PRGB32);
    image_buffer.resize(size.w * size.h * 4);


    // YGNodeStyleSetWidth((YGNodeRef)getRef(), size.w);
    // YGNodeStyleSetHeight((YGNodeRef)getRef(), size.h);
    // YGNodeStyleSetDisplay((YGNodeRef)getRef(), YGDisplayFlex);
    // YGNodeStyleSetFlexDirection((YGNodeRef)getRef(), YGFlexDirectionRow);
    // YGNodeSetAlwaysFormsContainingBlock((YGNodeRef)getRef(), true /*alwaysFormsContainingBlock*/);
}

c_window::~c_window()
{
}

std::vector<uint8_t> &c_window::get_image_buffer()
{
    return image_buffer;
}

void c_window::add_child(c_node *node)
{
    c_node::add_child(node);
}

void c_window::render(BLContext &context)
{

    bool _dirty_layout = false;

    if (!require_rerender(_dirty_layout))
        return;

    std::cout << "c_window::render " << std::endl;

    if (_dirty_layout)
    {
        YGNodeCalculateLayout((YGNodeRef)getRef(), 800.f, 600.f, YGDirectionLTR);
        std::cout << "c_window::layout update " << std::endl;
        BLPointI point = BLPointI(YGNodeLayoutGetLeft((YGNodeRef)getRef()), YGNodeLayoutGetTop((YGNodeRef)getRef()));

        layout_update(point);
        dirty_layout = false;
    }
    context.clearAll();

   std::vector<c_node*> absolute_nodes;
    for(auto& node :  c_app_context::get_current()->_nodes) {
        if (node->node_ref == nullptr) {
            std::cout << "found null noderef " << std::endl;
            continue;;
        }
        if ( YGNodeStyleGetPositionType((YGNodeRef)node->getRef()) == YGPositionTypeAbsolute && node->_style->get_z_index()  > 0)
            absolute_nodes.push_back(node);
    }

    c_node::render(context);




    std::sort(absolute_nodes.begin(), absolute_nodes.end(), [](const c_node* a, const c_node* b)
              { return a->_style->get_z_index() > b->_style->get_z_index(); });
    for(auto& node : absolute_nodes)
        node->render(context);

    context.end();

    BLImageData data;
    texture.getData(&data);

    memcpy(image_buffer.data(), data.pixelData, image_buffer.size());

    MessageBox(0, "WriteTofile", "merge", MB_OK);

    texture.writeToFile("claudiu.png");
    dirty = false;

    _updated = true;
}
void c_window::on_event(c_node_event *event)
{

    for (int i =  c_app_context::get_current()->_nodes.size() - 1; i > 0; i--)
    {
        if ( c_app_context::get_current()->_nodes.at(i) == this)
            continue;
        if (event->_stop_propagation)
            continue;

         c_app_context::get_current()->_nodes.at(i)->handle_event(event);
    }
}
