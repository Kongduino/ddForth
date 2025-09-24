#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

using namespace std;

void drawText(char*);
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
bool handleDRAWSTACKSTRING();

SDL_Window* window;
SDL_Renderer* renderer;
static TTF_Font* font = NULL;

void drawLine(int x0, int y0, int x1, int y1) {
  SDL_RenderLine(renderer, (float)x0, (float)y0, (float)x1, (float)y1);
}

void foreColor(unsigned char r, unsigned char g, unsigned char b) {
  SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
}

void drawText(string mytext) {
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
  size_t measured_length;
  h = 16;
  TTF_MeasureString(font, (const char *)mytext.c_str(), 0, 0, &w, &measured_length);
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

bool handleCLS() {
  if (!handleDrawColor()) return false;
  SDL_RenderClear(renderer); // to clear the window with that color,
  return true;
}

bool handleDrawPixel() {
  int x0, y0;
  if (popIntegerFromStack(&y0) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawPixel y0 Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&x0) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawPixel x0 Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (renderer == NULL) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawPixel renderer == NULL!\n");
    logThis();
    return false;
  }
  xxxxxx = snprintf((char *)msg, 255, "handleDrawPixel %d,%d\n", x0, y0);
  logThis();
  drawPixel(x0, y0);
  return true;
}

bool handleDrawLine() {
  // void drawLine(SDL_Renderer* renderer, float x0, float y0, float x1, float y1);
  int x0, y0, x1, y1;
  if (checkTypes(4, xINTEGER)) {
    if (popIntegerFromStack(&y1) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleDrawLine y1 Missing Integer on stack!\n");
      logThis();
      return false;
    }
    if (popIntegerFromStack(&x1) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleDrawLine x1 Missing Integer on stack!\n");
      logThis();
      return false;
    }
    if (popIntegerFromStack(&y0) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleDrawLine y0 Missing Integer on stack!\n");
      logThis();
      return false;
    }
    if (popIntegerFromStack(&x0) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleDrawLine x0 Missing Integer on stack!\n");
      logThis();
      return false;
    }
  } else if (checkTypes(4, xFLOAT)) {
    float fx0, fx1, fy0, fy1;
    if (popFloatFromStack(&fy1) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleDrawLine y1 Missing Float on stack!\n");
      logThis();
      return false;
    }
    if (popFloatFromStack(&fx1) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleDrawLine x1 Missing Float on stack!\n");
      logThis();
      return false;
    }
    if (popFloatFromStack(&fy0) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleDrawLine y0 Missing Float on stack!\n");
      logThis();
      return false;
    }
    if (popFloatFromStack(&fx0) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleDrawLine x0 Missing Float on stack!\n");
      logThis();
      return false;
    }
    x0 = fx0;
    y0 = fy0;
    x1 = fx1;
    y1 = fy1;
  }
  if (renderer == NULL) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawLine renderer == NULL!\n");
    logThis();
    return false;
  }
  xxxxxx = snprintf(
    (char *)msg, 255, "handleDrawLine %d,%d to %d,%d\n",
    x0, y0, x1, y1);
  logThis();
  drawLine(x0, y0, x1, y1);
  return true;
}

bool handleDrawColor() {
  // void foreColor(unsigned char r, unsigned char g, unsigned char b);
  int r, g, b;
  if (popIntegerFromStack(&b) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawColor b Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&g) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawColor g Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&r) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawColor r Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (renderer == NULL) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawColor renderer == NULL!\n");
    logThis();
    return false;
  }
  xxxxxx = snprintf(
  (char *)msg, 255, "handleDrawColor %d:%d:%d\n",
  r, g, b
  );
  logThis();
  foreColor(r, g, b);
  return true;
}

bool handleFillRect() {
  // void drawLine(SDL_Renderer* renderer, float x0, float y0, float x1, float y1);
  int x0, y0, w, h;
  if (popIntegerFromStack(&h) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleFillRect h Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&w) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleFillRect w Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&y0) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleFillRect y0 Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&x0) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleFillRect x0 Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (renderer == NULL) {
    xxxxxx = snprintf((char *)msg, 255, "handleFillRect renderer == NULL!\n");
    logThis();
    return false;
  }
  xxxxxx = snprintf(
  (char *)msg, 255, "handleFillRect %d,%d to %d,%d\n",
  x0, y0, (x0 + w - 1), (y0 + h - 1)
  );
  logThis();
  fillRect(x0, y0, w, h);
  return true;
}

bool handleDrawRect() {
  // void drawLine(SDL_Renderer* renderer, float x0, float y0, float x1, float y1);
  int x0, y0, w, h;
  if (popIntegerFromStack(&h) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawRect h Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&w) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawRect w Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&y0) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawRect y0 Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&x0) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawRect x0 Missing Integer on stack!\n");
    logThis();
    return false;
  }
  if (renderer == NULL) {
    xxxxxx = snprintf((char *)msg, 255, "handleDrawRect renderer == NULL!\n");
    logThis();
    return false;
  }
  xxxxxx = snprintf(
  (char *)msg, 255, "handleDrawRect %d,%d to %d,%d\n",
  x0, y0, (x0 + w - 1), (y0 + h - 1)
  );
  logThis();
  drawRect(x0, y0, w, h);
  return true;
}

extern bool insideString;

bool handleDRAWSTRING() {
  isPrinting = false;
  isDrawing = true;
  insideString = true;
  return true;
}

bool handleDRAWSTACKSTRING() {
  string s;
  if(popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleDRAWSTACKSTRING");
    return false;
  }
  drawText(s.c_str());
  return true;
}

bool handleFONT() {
  if (dataStack.at(dataStack.size() - 1) != xSTRING) {
    logInconsistent((char *)"handleFONT");
    return false;
  }
  string s;
  if(popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleFONT");
    return false;
  }
  char fname[256];
  xxxxxx = snprintf(fname, 255, "./Fonts/%s.ttf", s.c_str());
  font = TTF_OpenFont(fname, 32.0f);
  if (!font) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    return false;
  }
  return true;
}

bool handleRefresh() {
  SDL_RenderPresent(renderer);
  return true;
}

bool handleWIDTH() {
  int h, w;
  SDL_GetWindowSize(window, &w, &h);
  putIntegerOnStack(w);
  return true;
}

bool handleHEIGHT() {
  int h, w;
  SDL_GetWindowSize(window, &w, &h);
  putIntegerOnStack(h);
  return true;
}


