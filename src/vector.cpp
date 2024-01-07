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
    Vector3 rotatedVector = Vector3(
            this->x,
            this->y * cos(angle) - this->z * sin(angle),
            this->y * sin(angle) + this->z * cos(angle)
    );
    this->y = rotatedVector.y;
    this->z = rotatedVector.z;
}

void Vector3::rotateAroundY(float angle) {
    Vector3 rotatedVector = Vector3(
            this->x * cos(angle) - this->z * sin(angle),
            this->y,
            this->x * sin(angle) + this->z * cos(angle)
    );
    this->x = rotatedVector.x;
    this->z = rotatedVector.z;
}

void Vector3::rotateAroundZ(float angle) {
    Vector3 rotatedVector = Vector3(
            this->x * cos(angle) - this->y * sin(angle),
            this->x * sin(angle) + this->y * cos(angle),
            this->x
    );
    this->x = rotatedVector.x;
    this->y = rotatedVector.y;
}
