#include <base/font.hpp>
#include <blend2d.h>
#include <base/font_face.hpp>

c_font::c_font(c_font_face* face, float size) : _face(face) {
  if (_font.createFromFace(face->get(), size) != BLResultCode::BL_SUCCESS)
    assert("Failed to create font from font face.");
}

