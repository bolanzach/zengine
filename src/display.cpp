#include "display.h"

//// header vars
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* colorBufferTexture;

// Notice that this is a pointer. It acts as an array of memory where the pointer is
// the first element in the allocated array.
color_t* colorBuffer = nullptr;

int windowWidth = 800;
int windowHeight = 500;

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

void destroyWindow() {
    free(colorBuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void renderColorBuffer() {
    SDL_UpdateTexture(
        colorBufferTexture,
        nullptr,
        colorBuffer,
        (int) (windowWidth * sizeof(color_t))
    );
    SDL_RenderCopy(renderer, colorBufferTexture, nullptr, nullptr);
}

void clearColorBuffer(color_t color) {
    for (int y = 0; y < windowHeight; y++) {
        for (int x = 0; x < windowWidth; x++) {
            drawPixel(x, y, color);
        }
    }
}

void drawPixel(int x, int y, color_t color) {
    if (x >= 0 && x < windowWidth && y >= 0 && y < windowHeight) {
        colorBuffer[(windowWidth * y) + x] = color;
    }
}

void drawLineDDA(int x0, int y0, int x1, int y1, color_t color) {
    // Run
    int dx = x1 - x0;

    // Rise
    int dy = y1 - y0;

    // Which side (x | y) is longer
    int longestSideSteps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // How much should we increment x and y
    float xIncrement = dx / (float) longestSideSteps;
    float yIncrement = dy / (float) longestSideSteps;

    float currentX = x0;
    float currentY = y0;

    for (int i = 0; i <= longestSideSteps; i++) {
        drawPixel(round(currentX), round(currentY), color);
        currentX += xIncrement;
        currentY += yIncrement;
    }
}

void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
    drawLineDDA(x0, y0, x1, y1, color);
    drawLineDDA(x1, y1, x2, y2, color);
    drawLineDDA(x2, y2, x0, y0, color);
}
