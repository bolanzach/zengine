#include <iostream>
#include "SDL.h"
#include "display.h"
#include "vector.h"

#define NUMBER_OF_POINTS (9 * 9 * 9)
Vector3 cubePoints[NUMBER_OF_POINTS];
Vector2 projectedPoints[NUMBER_OF_POINTS];
float tempCubeRotation = 0;

bool isRunning = false;
uint previousFrameTime = 0;

float fieldOfViewFactor = 640;
Vector3 cameraPosition = Vector3(0, 0, -5);

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

    int point_count = 0;

    // Start loading my array of vectors
    // From -1 to 1 (in this 9x9x9 cube)
    for (float x = -1; x <= 1; x += 0.25) {
        for (float y = -1; y <= 1; y += 0.25) {
            for (float z = -1; z <= 1; z += 0.25) {
                Vector3 newPoint = Vector3(x, y, z);
                cubePoints[point_count++] = newPoint;
            }
        }
    }

    std::cout << cubePoints[0].x << std::endl;
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

    tempCubeRotation += 0.01;

    for (int i = 0; i < NUMBER_OF_POINTS; i++) {
        Vector3 point = cubePoints[i];

        // Rotate the point
        point.rotateAroundY(tempCubeRotation);

        // Translate vertex away from the camera
        point.z -= cameraPosition.z;

        // Project the current point
        Vector2 projectedPoint = project(point);

        // Save the projected 2D vector in the array of projected points
        projectedPoints[i] = projectedPoint;
    }
}

void render() {
    for (auto point : projectedPoints) {
        drawPixel(
                point.x + (windowWidth / 2),
                point.y + (windowHeight / 2),
                0xFFFFFF00
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
