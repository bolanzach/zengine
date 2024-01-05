#include <iostream>
#include "SDL.h"
#include "display.h"
#include "vector.h"

bool isRunning = false;
uint previousFrameTime = 0;

float fieldOfViewFactor = 640;
Vector3 cameraPosition = Vector3(0, 0, -5);

void setup() {
    isRunning = initializeWindow();

    // *** This is where we allocate memory to hold all the pixels ***
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
}

// Receives a 3D point and projects it to a 2D point
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

    drawPixel(100, 100, 0xFFFF0000);
    drawPixel(101, 100, 0xFFFF0000);
    drawPixel(101, 101, 0xFFFF0000);
    drawPixel(100, 101, 0xFFFF0000);

    Vector2 point1 = { 100, 200 };
    Vector2 point2 = { 400, 400 };

    drawLineDDA(point1.x, point1.y, point2.x, point2.y, 0xFF00FF00);
}

void render() {
    renderColorBuffer();
    clearColorBuffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

void freeResources(void) {
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




