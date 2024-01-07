#include <iostream>
#include "SDL.h"
#include "display.h"
#include "vector.h"
#include "mesh.h"

bool isRunning = false;
uint previousFrameTime = 0;

float fieldOfViewFactor = 640;
Vector3 cameraPosition = Vector3(0, 0, -5);

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

    mesh.rotation.y += 0.01;

    // Iterate all the Faces on our Mesh
    for (auto face : mesh.faces) {
        Triangle2 projectedTriangle;
        Vector3* faceVertices = mesh.getFaceVertices(face);

        // Apply transformations to each vertex
        for (int j = 0; j < 3; j++) {
            Vector3 vertex = faceVertices[j];

            // Rotations
            vertex.rotateAroundX(mesh.rotation.x);
            vertex.rotateAroundY(mesh.rotation.y);
            vertex.rotateAroundZ(mesh.rotation.z);

            // Translate vertex away from the camera
            vertex.z -= cameraPosition.z;

            // Project the current point
            Vector2 projectedPoint = project(vertex);

            // Scale and translate the projected points to the middle of the screen
            projectedPoint.x += (windowWidth / 2);
            projectedPoint.y += (windowHeight / 2);

            projectedTriangle.points[j] = projectedPoint;
        }

        trianglesToRender.push_back(projectedTriangle);
        delete[] faceVertices;
    }
}

void render() {
    // Iterate each projected triangle and render the points
    for (auto triangle2 : trianglesToRender) {
        drawTriangle(
                triangle2.points[0].x,
                triangle2.points[0].y,
                triangle2.points[1].x,
                triangle2.points[1].y,
                triangle2.points[2].x,
                triangle2.points[2].y,
                0xFF00FF00
        );
    }

    renderColorBuffer();
    clearColorBuffer(0xFF000000);

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
