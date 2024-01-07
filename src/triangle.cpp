#include "triangle.h"

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

Face::Face(int a, int b, int c) {
    this->a = a;
    this->b = b;
    this->c = c;
}
