//
// Created by Denis Topor on 01.07.2024.
//
#include <iostream>
#include "c_text.hpp"
#include <base/style/style_manager.hpp>

c_text::c_text()
{
    is_text = true;

    YGNodeSetContext(node_ref, this);
    YGNodeSetMeasureFunc(node_ref, &c_text::measure);
}

c_text::~c_text(){
    std::cout << "c_text destructed " << std::endl;
}
void c_text::render(BLContext &context)
{
    c_node::render(context);

    if (!font)
        return;

    if (!_string.has_value())
        return;

    int y = box.y;

    auto& s = _string.value();

    char raw[128];
    s.access_string(raw);
    gb.setUtf8Text((const char *)(&raw[0]));
    font.shape(gb);
    BLTextMetrics tm;
    BLFontMetrics fm = font.metrics();

    font.getTextMetrics(gb, tm);

    context.fillGlyphRun(BLPoint(box.x, box.y + fm.capHeight),
                         font, gb.glyphRun(), _style->_color);

    // y += fm.ascent + fm.descent + fm.lineGap;
}

YGSize c_text::measure(YGNodeConstRef node,
                       float width,
                       YGMeasureMode widthMode,
                       float height,
                       YGMeasureMode heightMode)
{

    std::cout << "c_text::measure called" << std::endl;
    auto item = reinterpret_cast<c_text *>(YGNodeGetContext(node));

    auto &gb = item->gb;
    auto &font = item->font;

    if (!item->_string.has_value()) {
        std::cout << "Warrning c_text without string!! " << std::endl;
        return {0,0};
    }
    auto& s = item->_string.value();

    char raw[128];
    s.access_string(raw);
    gb.setUtf8Text((const char *)(&raw[0]));

    font.shape(gb);
    BLTextMetrics tm;
    BLFontMetrics fm = font.metrics();

    font.getTextMetrics(gb, tm);

    float w = (tm.boundingBox.x1 - tm.boundingBox.x0);
    float h = fm.capHeight;

    YGSize size{w, h};

    return size;
}
