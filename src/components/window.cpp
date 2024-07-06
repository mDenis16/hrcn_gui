#include "../base/node.hpp"
#include "window.hpp"

#include <fstream>

c_window::c_window(BLSizeI size)
{
    is_root = true;
    texture = BLImage(1280, 720, BL_FORMAT_PRGB32);
    image_buffer.resize(1280 * 720 * 4);

    YGNodeStyleSetWidth(node_ref, size.w);
    YGNodeStyleSetHeight(node_ref, size.h);
    YGNodeStyleSetDisplay(node_ref, YGDisplayFlex);
    YGNodeStyleSetFlexDirection(node_ref, YGFlexDirectionRow);
    YGNodeSetAlwaysFormsContainingBlock(node_ref, true /*alwaysFormsContainingBlock*/);
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
void writeBufferToFile(const std::string &filename, const uint8_t *buffer, size_t size)
{
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile)
    {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    outFile.write(reinterpret_cast<const char *>(buffer), size);
    if (!outFile)
    {
        std::cerr << "Error writing to file: " << filename << std::endl;
    }
    outFile.close();
}

void c_window::render(BLContext &context)
{

    bool _dirty_layout = false;

    if (!require_rerender(_dirty_layout))
        return;

    if (_dirty_layout)
    {
        YGNodeCalculateLayout(YGNodeGetOwner(node_ref), YGUndefined, YGUndefined, YGDirectionLTR);

        BLPointI point = BLPointI(YGNodeLayoutGetLeft(YGNodeGetOwner(node_ref)), YGNodeLayoutGetTop(YGNodeGetOwner(node_ref)));

        layout_update(point);
        
    }
    context.clearAll();

    c_node::render(context);

    context.end();

    BLImageData data;
    texture.getData(&data);

    memcpy(image_buffer.data(), data.pixelData, image_buffer.size());

    dirty = false;

    _updated = true;
}
void c_window::on_event(c_node_event *event)
{

    for (int i = nodes.size() - 1; i > 0; i--)
    {
        if (nodes.at(i) == this)
            continue;
        if (event->_stop_propagation)
            continue;

        nodes.at(i)->handle_event(event);
    }
}
