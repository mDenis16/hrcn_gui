#include <base/font.hpp>
#include <blend2d.h>
#include <base/font_face.hpp>

c_font::c_font(c_font_face* face, float size) : _face(face) {
  _font.createFromFace(face->get(), size);
}

