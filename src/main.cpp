#include <iostream>
#include "SDL.h"
#include "color.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"

bool isRunning = false;
uint previousFrameTime = 0;

float fieldOfViewFactor = 640;
Vector3 cameraPosition = Vector3(0, 0, 0);

Mesh mesh;
std::vector<Triangle2> trianglesToRender = std::vector<Triangle2>();

void setup() {
    isRunning = initializeWindow();

    /// This is where we allocate memory to hold all the pixels
    colorBuffer = (color_t*) malloc(sizeof(color_t) * windowWidth * windowHeight);
    assert(colorBuffer);

    // Texture used to display the color_buffer
    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        windowWidth,
        windowHeight
    );

    mesh = loadObjFileDataToMesh("../assets/free_car.obj");
}

// Receives a 3D point and projects it to a 2D point. This is using left-handed coordinate system
Vector2 project(Vector3 point) {
    Vector2 projectedPoint = Vector2(
            (point.x * fieldOfViewFactor) / point.z,
            (point.y * fieldOfViewFactor) / point.z);

    return projectedPoint;
}

void processInput() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
    }
}

void update() {
    int waitTime = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime);
    if (waitTime > 0 && waitTime < FRAME_TARGET_TIME) {
        SDL_Delay(waitTime);
    }

    previousFrameTime = SDL_GetTicks();

    trianglesToRender.clear();

    mesh.rotation.y += 0.05;
    //mesh.rotation.z += 0.05;

    // Iterate all the Faces on our Mesh
    for (auto face : mesh.faces) {
        Vector3 transformedVertices[3];
        Vector3* faceVertices = mesh.getFaceVertices(face);

        // Apply transformations to each vertex of the Face
        for (int i = 0; i < 3; i++) {
            Vector3 vertex = faceVertices[i];

            // Rotations
            vertex.rotateAroundX(mesh.rotation.x);
            vertex.rotateAroundY(mesh.rotation.y);
            vertex.rotateAroundZ(mesh.rotation.z);

            // Translate vertex away from the camera
//            vertex.z -= cameraPosition.z;
            vertex.z += 5;

            transformedVertices[i] = vertex;
        }

        // Backface culling
        // @efficiency may be another algorithm for this
        Vector3 vectorA = transformedVertices[0];
        Vector3 vectorB = transformedVertices[1];
        Vector3 vectorC = transformedVertices[2];

        Vector3 vectorAB = vectorB.subtract(vectorA).getNormalizedVector();
        Vector3 vectorAC = vectorC.subtract(vectorA).getNormalizedVector();

        // Compute the Face normal to find the perpendicular vector on the Face
        // Tbe order matters based on the handiness of the coordinate system
        Vector3 normalVector = vectorAB.crossProduct(vectorAC);

        // Normalize the normal vector
        normalVector.normalize();

        // Find the vector between a point in the Face and the camera origin
        Vector3 cameraRay = cameraPosition.subtract(vectorA);

        // Check the alignment of the camera ray and the Face normal
        float alignment = normalVector.dotProduct(cameraRay);

        // Skip this Face if it's not facing the camera
        if (alignment < 0) {
            continue;
        }

        // Project the 3 vertices of the Face
        Triangle2 projectedTriangle;
        for (int i = 0; i < 3; i++) {
            Vector3 vertex = transformedVertices[i];

            // Project the current point
            Vector2 projectedPoint = project(vertex);

            // Scale and translate the projected points to the middle of the screen
            projectedPoint.x += (windowWidth / 2);
            projectedPoint.y += (windowHeight / 2);

            projectedTriangle.points[i] = projectedPoint;
        }

        trianglesToRender.push_back(projectedTriangle);
        delete[] faceVertices;
    }
}

void render() {
    // Iterate each projected triangle and render the points
    for (auto triangle2 : trianglesToRender) {
        triangle2.drawFilled(COLOR_RED);
        triangle2.drawOutline();
    }

    renderColorBuffer();
    clearColorBuffer(COLOR_BLACK);

    SDL_RenderPresent(renderer);
}

void freeResources() {
    destroyWindow();
//    array_free(global_mesh.faces);
//    array_free(global_mesh.vertices);
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    setup();

    while (isRunning) {
        processInput();
        update();
        render();
    }

    freeResources();

    return 0;
}
