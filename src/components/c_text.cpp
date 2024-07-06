//
// Created by Denis Topor on 01.07.2024.
//
#include <iostream>
#include "c_text.hpp"
#include <base/style/style_manager.hpp>

c_text::c_text()
{

    YGNodeSetContext(node_ref, this);
    YGNodeSetMeasureFunc(node_ref, &c_text::measure);
}

void c_text::render(BLContext &context)
{
    c_node::render(context);

    if (!font)
        return;

    const char *str =
        "Hello Blend2D!\n";

    int y = box.y;

    gb.setUtf8Text((const char *)(&local_Str[0]));
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

    auto item = reinterpret_cast<c_text *>(YGNodeGetContext(node));

    auto &gb = item->gb;
    auto &font = item->font;

    gb.setUtf8Text((const char *)(&item->local_Str[0]));
    font.shape(gb);
    BLTextMetrics tm;
    BLFontMetrics fm = font.metrics();

    font.getTextMetrics(gb, tm);

    float w = (tm.boundingBox.x1 - tm.boundingBox.x0);
    float h = fm.capHeight;

    YGSize size{w, h};

    return size;
}
