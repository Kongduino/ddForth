#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

using namespace std;

SDL_Renderer* renderer;
static TTF_Font* font = NULL;

void drawLine(int x0, int y0, int x1, int y1) {
  SDL_RenderLine(renderer, (float)x0, (float)y0, (float)x1, (float)y1);
}

void foreColor(unsigned char r, unsigned char g, unsigned char b) {
  SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void drawText(string mytext) {
  cout << " DRAW TEXT ";
  int r, g, b;
  int x, y, w, h;
  if (popIntegerFromStack(&b) == false) {
    xxxxxx = snprintf((char *)msg, 255, "drawText b Missing Integer on stack!\n");
    logThis();
    return;
  }
  if (popIntegerFromStack(&g) == false) {
    xxxxxx = snprintf((char *)msg, 255, "drawText g Missing Integer on stack!\n");
    logThis();
    return;
  }
  if (popIntegerFromStack(&r) == false) {
    xxxxxx = snprintf((char *)msg, 255, "drawText r Missing Integer on stack!\n");
    logThis();
    return;
  }
  if (popIntegerFromStack(&h) == false) {
    xxxxxx = snprintf((char *)msg, 255, "drawText h Missing Integer on stack!\n");
    logThis();
    return;
  }
  if (popIntegerFromStack(&w) == false) {
    xxxxxx = snprintf((char *)msg, 255, "drawText w Missing Integer on stack!\n");
    logThis();
    return;
  }
  if (popIntegerFromStack(&y) == false) {
    xxxxxx = snprintf((char *)msg, 255, "drawText y Missing Integer on stack!\n");
    logThis();
    return;
  }
  if (popIntegerFromStack(&x) == false) {
    xxxxxx = snprintf((char *)msg, 255, "drawText x Missing Integer on stack!\n");
    logThis();
    return;
  }
  SDL_Color color = { (Uint8)r, (Uint8)g, (Uint8)b, SDL_ALPHA_OPAQUE };
  SDL_Surface* text;
  SDL_Texture* texture = NULL;
  text = TTF_RenderText_Blended(font, mytext.c_str(), 0, color);
  if (text) {
    texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_DestroySurface(text);
  }
  if (!texture) {
    SDL_Log("Couldn't create text: %s\n", SDL_GetError());
    return;
  }
  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = w;
  dstrect.h = h;
  {
    SDL_FRect d;
    d.x = (float)dstrect.x;
    d.y = (float)dstrect.y;
    d.w = (float)dstrect.w;
    d.h = (float)dstrect.h;
    SDL_RenderTexture(renderer, texture, NULL, &d);
  }
}

void drawPixel(int x, int y) {
  // SDL_DECLSPEC bool SDLCALL SDL_RenderPoint(SDL_Renderer *renderer, float x, float y);
  SDL_RenderPoint(renderer, (float)x, (float)y); // Draw the pixel
}

void fillRect(int x0, int y0, int w, int h) {
  SDL_FRect rect;
  rect.x = (float)x0;
  rect.y = (float)y0;
  rect.w = (float)w;
  rect.h = (float)h;
  SDL_RenderFillRect(renderer, &rect);
}

void drawRect(int x0, int y0, int w, int h) {
  SDL_FRect rect;
  rect.x = (float)x0;
  rect.y = (float)y0;
  rect.w = (float)w;
  rect.h = (float)h;
  SDL_RenderRect(renderer, &rect);
}
