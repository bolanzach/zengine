#include <cmath>
#include "vector.h"

Vector2::Vector2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2::Vector2() {
    this->x = 0;
    this->y = 0;
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

void Vector3::rotateAroundX(float angle) {
    this->y = this->y * cos(angle) - this->z * sin(angle);
    this->z = this->y * sin(angle) + this->z * cos(angle);
}

void Vector3::rotateAroundY(float angle) {
    this->x = this->x * cos(angle) - this->z * sin(angle);
    this->z = this->x * sin(angle) + this->z * cos(angle);
}

void Vector3::rotateAroundZ(float angle) {
    this->x = this->x * cos(angle) - this->y * sin(angle);
    this->y = this->x * sin(angle) + this->y * cos(angle);
}
