#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

// bool SDL_RenderDebugTextFormat(SDL_Renderer *renderer, float x, float y, const char *fmt, ...);
static TTF_Font* font = NULL;
static SDL_Texture* texture = NULL;

int main(int argc, char* argv[]) {
  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init()) {
    SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
  // Create a window
  SDL_Window* window = SDL_CreateWindow("SDL3 Basic Example", 800, 600, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  // Create a renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == NULL) {
    SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  // Main loop flag
  int quit = 0;
  // Event handler
  SDL_Event e;
  // Main application loop
  font = TTF_OpenFont("/Users/dda/Coding/Development_Forth/ddForth/Geneva.ttf", 18.0f);
  if (!font) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    return -1;
  }
  while (!quit) {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_EVENT_QUIT) {
        quit = 1;
      }
    }
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);  // White background
    SDL_RenderClear(renderer);
    // Set drawing color to red
    // Draw a line from (100, 100) to (400, 300)
    int count = 0;
    unsigned char red = 128;
    unsigned char blue = 0;
    unsigned char green = 0;
    float step = 2.1;
    for (float x = 100.0; x < 400.0; x += step) {
      SDL_SetRenderDrawColor(renderer, 192, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderLine(renderer, x, 100.0f, 400.0f, x);
      SDL_SetRenderDrawColor(renderer, 0, 192, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderLine(renderer, 400.0f, x, 500.0f - x, 500.0f);
      SDL_SetRenderDrawColor(renderer, 0, 0, 192, SDL_ALPHA_OPAQUE);
      SDL_RenderLine(renderer, 500.0f - x, 500.0f, 100.0, 500.0 - x);
      SDL_SetRenderDrawColor(renderer, 192, 192, 192, SDL_ALPHA_OPAQUE);
      SDL_RenderLine(renderer, 100.0, 500.0 - x, x, 100.0);
    }
    SDL_RenderDebugTextFormat(renderer, 555.0, 100.0, "Hello...");

    SDL_Surface* text;
    SDL_Color color = { 128, 255, 0, SDL_ALPHA_OPAQUE };
    text = TTF_RenderText_Blended(font, "Hello World!", 0, color);
    if (text) {
      texture = SDL_CreateTextureFromSurface(renderer, text);
      SDL_DestroySurface(text);
    }
    if (!texture) {
      SDL_Log("Couldn't create text: %s\n", SDL_GetError());
      return -1;
    }
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_Rect dstrect;
    dstrect.x = 500;
    dstrect.y = 120;
    dstrect.w = 180;
    dstrect.h = 32;
    {
      SDL_FRect d;
      d.x = (float)dstrect.x;
      d.y = (float)dstrect.y;
      d.w = (float)dstrect.w;
      d.h = (float)dstrect.h;
      SDL_RenderTexture(renderer, texture, NULL, &d);
    }
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
  }
  // Clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}