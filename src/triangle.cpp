#include <algorithm>

#include "triangle.h"
#include "display.h"
#include "color.h"

/// Draw the top of the triangle so that the bottom is flat
void fillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    // Calculate the slope of the left and right edges
    float slopeLeft = (float)(x1 - x0) / (float)(y1 - y0);
    float slopeRight = (float)(x2 - x0) / (float)(y2 - y0);

    // Calculate the x values for each edge
    float xLeft = x0;
    float xRight = x0;

    // Iterate each row of the triangle
    for (int y = y0; y <= y1; y++) {
        // Draw the row
        drawLineDDA(xLeft, y, xRight, y, color);

        // Increment the x values
        xLeft += slopeLeft;
        xRight += slopeRight;
    }
}

/// Draw the bottom of the triangle so that the top is flat
void fillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    // Calculate the slope of the left and right edges
    float slopeLeft = (float)(x2 - x0) / (float)(y2 - y0);
    float slopeRight = (float)(x2 - x1) / (float)(y2 - y1);

    // Calculate the x values for each edge
    float xLeft = x2;
    float xRight = x2;

    // Iterate each row of the triangle
    for (int y = y2; y > y0; y--) {
        // Draw the row
        drawLineDDA(xLeft, y, xRight, y, color);

        // Increment the x values
        xLeft -= slopeLeft;
        xRight -= slopeRight;
    }
}

Triangle2::Triangle2() {
    this->points[0] = Vector2();
    this->points[1] = Vector2();
    this->points[2] = Vector2();
}

Triangle2::Triangle2(Vector2 a, Vector2 b, Vector2 c) {
    this->points[0] = a;
    this->points[1] = b;
    this->points[2] = c;
}

void Triangle2::drawOutline() {
    int x0 = this->points[0].x;
    int y0 = this->points[0].y;
    int x1 = this->points[1].x;
    int y1 = this->points[1].y;
    int x2 = this->points[2].x;
    int y2 = this->points[2].y;

    color_t color = COLOR_BLUE;

    drawLineDDA(x0, y0, x1, y1, color);
    drawLineDDA(x1, y1, x2, y2, color);
    drawLineDDA(x2, y2, x0, y0, color);
}

// @efficiency a better algorithm probably exists
void Triangle2::drawFilled(color_t color) {
    int x0 = this->points[0].x;
    int y0 = this->points[0].y;
    int x1 = this->points[1].x;
    int y1 = this->points[1].y;
    int x2 = this->points[2].x;
    int y2 = this->points[2].y;

    // Sort the vertices by y value ascending (y0 < y1 < y2)
    if (y1 < y0) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }
    if (y2 < y1) {
        std::swap(y1, y2);
        std::swap(x1, x2);
    }
    if (y1 < y0) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }

    // Check for special cases where we need to only draw a flat triangle
    if (y1 == y2) {
        fillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, color);
        return;
    } else if (y0 == y1) {
        fillFlatTopTriangle(x0, y0, x1, y1, x2, y2, color);
        return;
    }

    // Calculate the midpoint (mx, my) using triangle similarity
    int my = y1;
    int mx = ((float)((x2 - x0) * (y1 - y0)) / (float)(y2 - y0)) + x0;

    fillFlatBottomTriangle(x0, y0, x1, y1, mx, my, color);
    fillFlatTopTriangle(x1, y1, mx, my, x2, y2, color);
}

Face::Face(int a, int b, int c) {
    this->a = a;
    this->b = b;
    this->c = c;
}
