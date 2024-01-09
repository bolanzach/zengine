#ifndef ZENGINE_VECTOR_H
#define ZENGINE_VECTOR_H

class Vector2 {
public:
    float x;
    float y;

    Vector2(float x, float y);
    Vector2();

    float getMagnitude() const;
    Vector2 add(Vector2 vector);
    Vector2 subtract(Vector2 vector);
    Vector2 multiply(float scalar);
    Vector2 divide(float scalar);
};

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z);
    Vector3();

    void rotateAroundX(float angle);
    void rotateAroundY(float angle);
    void rotateAroundZ(float angle);

    float getMagnitude() const;
    Vector3 add(Vector3 vector);
    Vector3 subtract(Vector3 vector);
    Vector3 multiply(float scalar);
    Vector3 divide(float scalar);
    Vector3 crossProduct(Vector3 vector);
    float dotProduct(Vector3 vector);
};

#endif //ZENGINE_VECTOR_H
