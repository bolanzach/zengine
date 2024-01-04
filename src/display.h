#include "SDL.h"

typedef uint32_t color_t;

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* colorBufferTexture;

extern color_t* colorBuffer;
extern int windowWidth;
extern int windowHeight;


bool initializeWindow();
void renderColorBuffer(void);
void clearColorBuffer(color_t color);
void drawPixel(int x, int y, color_t color);