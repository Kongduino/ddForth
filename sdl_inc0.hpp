#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL_video.h>

void drawText(char*, float, float);
bool handleDrawPixel();
bool handleDrawLine();
bool handleDrawColor();
void foreColor(unsigned char, unsigned char, unsigned char);
void drawLine(int, int, int, int);
void drawPixel(int, int);
void fillRect(int, int, int, int);
bool handleFillRect();
void drawRect(int, int, int, int);
bool handleDrawRect();
bool handleCLS();
bool handleDRAWSTRING();
bool handleFONT();

bool isDrawing = false;
