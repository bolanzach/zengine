#include <iostream>
#include "SDL.h"
#include "display.h"

bool isRunning = false;

void setup() {
    isRunning = initializeWindow();

    // *** This is where we allocate memory to hold all the pixels ***
    colorBuffer = (color_t*) malloc(sizeof(color_t) * windowWidth * windowHeight);

    // Texture used to display the color_buffer
    colorBufferTexture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        windowWidth,
        windowHeight
    );
}

void freeResources(void) {
    free(colorBuffer);
//    array_free(global_mesh.faces);
//    array_free(global_mesh.vertices);
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

void render() {


    drawPixel(100, 100, 0xFFFF0000);
    drawPixel(101, 100, 0xFFFF0000);
    drawPixel(101, 101, 0xFFFF0000);
    drawPixel(100, 101, 0xFFFF0000);
    renderColorBuffer();
    clearColorBuffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    setup();

    while (isRunning) {
        processInput();
        render();
    }

    freeResources();

    return 0;
}




