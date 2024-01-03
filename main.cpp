#include <iostream>
#include "SDL.h"

bool isRunning = false;

// header vars
SDL_Window* window;
SDL_Renderer* renderer;
int windowWidth;
int windowHeight;

bool initializeWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "error initializing SDL!\n");
        return false;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);

    windowWidth = displayMode.w;
    windowHeight = displayMode.h;

    window = SDL_CreateWindow(
            "Zengine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            500,
            SDL_WINDOW_SHOWN
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL Window!\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer!\n");
        return false;
    }

    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
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
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    isRunning = initializeWindow();

    while (isRunning) {
        processInput();
        render();
    }

    return 0;
}




