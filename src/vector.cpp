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

float Vector2::getMagnitude() const {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

Vector2 Vector2::add(Vector2 vector) {
    return {this->x + vector.x, this->y + vector.y};
}

Vector2 Vector2::subtract(Vector2 vector) {
    return {this->x - vector.x, this->y - vector.y};
}

Vector2 Vector2::multiply(float scalar) {
    return {this->x * scalar, this->y * scalar};
}

Vector2 Vector2::divide(float scalar) {
    return {this->x / scalar, this->y / scalar};
}

Vector3::Vector3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3() {
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
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

void Vector3::normalize() {
    Vector3 normal = this->getNormalizedVector();
    this->x = normal.x;
    this->y = normal.y;
    this->z = normal.z;
}

float Vector3::getMagnitude() const {
    return sqrt(
            pow(this->x, 2) +
            pow(this->y, 2) +
            pow(this->z, 2));
}

Vector3 Vector3::add(Vector3 vector) {
    return {this->x + vector.x, this->y + vector.y, this->z + vector.z};
}

Vector3 Vector3::subtract(Vector3 vector) {
    return {this->x - vector.x, this->y - vector.y, this->z - vector.z};
}

Vector3 Vector3::multiply(float scalar) {
    return {this->x * scalar, this->y * scalar, this->z * scalar};
}

Vector3 Vector3::divide(float scalar) {
    return {this->x / scalar, this->y / scalar, this->z / scalar};
}

Vector3 Vector3::crossProduct(Vector3 vector) {
    return {
            this->y * vector.z - this->z * vector.y,
            this->z * vector.x - this->x * vector.z,
            this->x * vector.y - this->y * vector.x
    };
}

float Vector3::dotProduct(Vector3 vector) {
    return (this->x * vector.x) + (this->y * vector.y) + (this->z * vector.z);
}

Vector3 Vector3::getNormalizedVector() {
    float magnitude = this->getMagnitude();
    return {this->x / magnitude, this->y / magnitude, this->z / magnitude};
}
