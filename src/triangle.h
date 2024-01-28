#ifndef ZENGINE_TRIANGLE_H
#define ZENGINE_TRIANGLE_H

#include "vector.h"

/// A Triangle is a collection of 3 Vector2 points. These are the actual (x,y) points on the screen
class Triangle2 {
public:
    Vector2 points[3];

    Triangle2(Vector2 a, Vector2 b, Vector2 c);
    Triangle2();

    void drawOutline();
    void drawFilled();
};

/// A Face is a Triangle in 3D space. It contains 3 fields that each are an index to a Vector3 in
/// a Mesh.
class Face {
public:
    int a;
    int b;
    int c;

    Face(int a, int b, int c);
};

#endif //ZENGINE_TRIANGLE_H
