#pragma once
#include <algorithm>
#include <blend2d.h>

namespace path_generator {
    std::pair<BLPoint, BLPoint> calculate_quadratic_bezier_control_points(BLPoint start, BLPoint end, double radius) {
        double angle = std::atan2(end.y - start.y, end.x - start.x);
        double dx = radius * std::cos(angle + M_PI_2);
        double dy = radius * std::sin(angle + M_PI_2);
        return std::make_pair(BLPoint(start.x + dx, start.y + dy), BLPoint(end.x - dx, end.y - dy));
    }
    void generate_rounded_rectangle(BLPath& path, float x, float y, float w, float h,
                            float topLeftRadius, float topRightRadius,
                            float bottomRightRadius, float bottomLeftRadius) {
        // Helper function to calculate control points for a quadratic Bézier curve approximation of an arc


       // radius = std::min(radius, w * 0.5f, h * 0.5f);

        auto width = w;
        auto height = h;

        path.clear();

        path.moveTo(x + topLeftRadius, y); // Start at the top-left corner, adjusted for radius

        // Top edge
        path.lineTo(x + w - topRightRadius, y);
        // Top-right corner
        path.cubicTo(x + w - topRightRadius / 2, y, x + w, y + topRightRadius / 2, x + w, y + topRightRadius);

        // Right edge
        path.lineTo(x + w, y + w - bottomRightRadius);
        // Bottom-right corner
        path.cubicTo(x + w, y + height - bottomRightRadius / 2, x + width - bottomRightRadius / 2, y + height, x + width - bottomRightRadius, y + height);

        // Bottom edge
        path.lineTo(x + bottomLeftRadius, y + height);
        // Bottom-left corner
        path.cubicTo(x + bottomLeftRadius / 2, y + height, x, y + height - bottomLeftRadius / 2, x, y + height - bottomLeftRadius);

        // Left edge
        path.lineTo(x, y + topLeftRadius);
        // Top-left corner
        path.cubicTo(x, y + topLeftRadius / 2, x + topLeftRadius / 2, y, x + topLeftRadius, y);
    }
    void generate_border(BLPath& path, float x, float y, float w, float h,
                           float topLeftRadius, float topRightRadius,
                           float bottomRightRadius, float bottomLeftRadius,
                           float topWidth,
                           float rightWidth,
                           float bottomWidth,
                           float leftWidth
                           ) {
        // Helper function to calculate control points for a quadratic Bézier curve approximation of an arc


        // radius = std::min(radius, w * 0.5f, h * 0.5f);

        auto width = w;
        auto height = h;

        path.clear();

        path.moveTo(x + topLeftRadius, y + topWidth); // Start at the top-left corner, adjusted for radius

        // Top edge
        path.lineTo(x + w - topRightRadius - rightWidth, y + topWidth );
        // Top-right corner
        path.cubicTo(x + w - topRightRadius / 2, y + topWidth, x + w, y + topRightRadius / 2 + topWidth, x + w - rightWidth, y + topRightRadius + topWidth);

        // Right edge
        path.lineTo(x + w - rightWidth, w - bottomRightRadius - std::max(bottomWidth, rightWidth));
        // Bottom-right corner
        path.cubicTo(x + w - rightWidth, y + height - bottomRightRadius / 2  - std::max(bottomWidth, rightWidth), x + width - bottomRightRadius / 2 - rightWidth,  y + height  - bottomWidth , x + width - bottomRightRadius - rightWidth, y + height  - bottomWidth);

        // Bottom edge
        path.lineTo(x + bottomLeftRadius - leftWidth, y + height - std::max(bottomWidth, leftWidth));
        // Bottom-left corner
        path.cubicTo(x + bottomLeftRadius / 2 + leftWidth,
            y + height  - bottomWidth, x + leftWidth,
            y + height - bottomLeftRadius / 2 - bottomWidth,
            x + leftWidth,
            y + height - bottomLeftRadius - std::max(bottomWidth, leftWidth));

        // Left edge
        path.lineTo(x + leftWidth, y + topLeftRadius + std::max(leftWidth, topWidth) );
        // Top-left corner
        path.cubicTo(x + leftWidth, y + topLeftRadius / 2 + std::max(leftWidth, topWidth), leftWidth + x + topLeftRadius / 2, y + std::max(leftWidth, topWidth), leftWidth + x + topLeftRadius, y + std::max(leftWidth, topWidth));


    }
}

