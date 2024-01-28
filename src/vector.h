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
    void normalize();

    float getMagnitude() const;
    Vector3 add(Vector3 vector);
    Vector3 subtract(Vector3 vector);
    Vector3 multiply(float scalar);
    Vector3 divide(float scalar);

    /// Use when only the direction is needed, not the magnitude (length)
    /// Transforms a Vector of any length int a unit vector (length = 1)
    Vector3 getNormalizedVector();

    /// Returns the normal vector, resulting in a perpendicular vector to the 2 vectors on a plane.
    /// The normal approaches zero as the vectors point in the same direction.
    Vector3 crossProduct(Vector3 vector);

    /// Returns a positive value if the vectors are in the same direction, negative otherwise.
    float dotProduct(Vector3 vector);
};

#endif //ZENGINE_VECTOR_H
