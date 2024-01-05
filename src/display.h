#include "SDL.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

typedef uint32_t color_t;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* colorBufferTexture;

extern color_t* colorBuffer;
extern int windowWidth;
extern int windowHeight;

bool initializeWindow();
void destroyWindow();
void renderColorBuffer(void);
void clearColorBuffer(color_t color);
void drawPixel(int x, int y, color_t color);
void drawLineDDA(int x0, int y0, int x1, int y1, color_t color);
void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
