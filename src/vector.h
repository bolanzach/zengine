#ifndef ZENGINE_VECTOR_H
#define ZENGINE_VECTOR_H

class Vector2 {
public:
    float x;
    float y;

    Vector2(float x, float y);
    Vector2();
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
};

#endif //ZENGINE_VECTOR_H
