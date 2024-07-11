#pragma once
#include <yoga/Yoga.h>
enum class e_flex_direction : uint8_t
{
  column = YGFlexDirectionColumn,
  column_reverse = YGFlexDirectionColumnReverse,
  row = YGFlexDirectionRow,
  row_reverse = YGFlexDirectionRowReverse,
};

enum class e_align : uint8_t
{
  flex_auto = YGAlignAuto,
  flex_start = YGAlignFlexStart,
  center = YGAlignCenter,
  flex_end = YGAlignFlexEnd,
  strech = YGAlignStretch,
  baseline = YGAlignBaseline,
  space_between = YGAlignSpaceBetween,
  space_around = YGAlignSpaceAround,
  space_evenly = YGAlignSpaceEvenly,
};
enum class e_justify : uint8_t
{
  flex_start = YGJustifyFlexStart,
  center = YGJustifyCenter,
  flex_end = YGJustifyFlexEnd,
  space_between = YGJustifySpaceBetween,
  space_around = YGJustifySpaceAround,
  space_evenly = YGJustifySpaceEvenly,
};

enum class e_gutter : uint8_t
{
  column = YGGutterColumn,
  row = YGGutterRow,
  all = YGGutterAll,
};
enum class e_edge : uint8_t
{
  left = YGEdgeLeft,
  top = YGEdgeTop,
  right = YGEdgeRight,
  bottom = YGEdgeBottom,
  start = YGEdgeStart,
  end = YGEdgeEnd,
  horizontal = YGEdgeHorizontal,
  vertical = YGEdgeVertical,
  all = YGEdgeAll,
};
enum class e_display : uint8_t
{
  flex = YGDisplayFlex,
  none = YGDisplayNone
};

enum class e_position : uint8_t
{
  position_type_static = YGPositionTypeStatic,
  position_type_relative = YGPositionTypeRelative,
  position_type_absolute = YGPositionTypeAbsolute,

};