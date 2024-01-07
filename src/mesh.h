#ifndef ZENGINE_MESH_H
#define ZENGINE_MESH_H

#include "vector"
#include "vector.h"
#include "triangle.h"

//// A Mesh is a collection of Triangles arranged in 3D space
class Mesh {
public:
    Mesh();

    /// All the Vertices in the Mesh
    std::vector<Vector3> vertices;

    /// All the Faces in the Mesh
    std::vector<Face> faces;

    /// The Mesh's rotation
    Vector3 rotation;

    /// Get the Mesh Vertices for a Face
    Vector3* getFaceVertices(const Face& face);
};

Mesh loadObjFileDataToMesh(const char* fileName);

#endif //ZENGINE_MESH_H
