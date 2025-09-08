#undef DEBUG
  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init()) {
    SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
  // Create a window
  SDL_Window* window = SDL_CreateWindow("ddForth SDL", 800, 600, SDL_WINDOW_RESIZABLE);
  if (window == NULL) {
    SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  // Create a renderer
  renderer = SDL_CreateRenderer(window, NULL);
  if (renderer == NULL) {
    SDL_Log("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  font = TTF_OpenFont("./Fonts/RobotoMono-Medium.ttf", 18.0f);
  if (!font) {
    SDL_Log("Couldn't open font: %s\n", SDL_GetError());
    return -1;
  }
  // Main loop flag
  int quit = 0;
  // Event handler
  SDL_Event e;
  // Main application loop
  strcpy(code, "-10 BEGIN DUP . DUP -1 * BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP 1 + DUP 0= UNTIL . .S CR");
  cout << code << endl;
  chunks = tokenize(code, chunks);
  strcpy(code, "127 127 127 CLS 300 0 DO 127 I I 3 + 2 / DRAWCOLOR I 100 300 I - 400 DRAWLINE 0 I 100 + 300 400 I - DRAWLINE LOOP");
  cout << code << endl;
  chunks = tokenize(code, chunks);

  strcpy(code, ": RNDCOL RANDOM RANDOM RANDOM DRAWCOLOR ; 0 BEGIN RNDCOL RANDOM 500 + RANDOM DRAWPIXEL 1 + DUP 800 > UNTIL");
  cout << code << endl;
  chunks = tokenize(code, chunks);

  strcpy(code, "0 BEGIN RNDCOL RANDOMI 400 MOD 368 + RANDOM 300 +  32 32 FILLRECT 1 + DUP 50 > UNTIL");
  cout << code << endl;
  chunks = tokenize(code, chunks);

  strcpy(code, "0 BEGIN RNDCOL RANDOMI 768 MOD RANDOMI 568 MOD  32 32 DRAWRECT 1 + DUP 100 > UNTIL");
  cout << code << endl;
  chunks = tokenize(code, chunks);

  strcpy(code, "WORDS CR 255 VAR r 0 VAR g 127 VAR b 1799 0 DO I 10.0 / 180 + SIN 50.0 * 100.0 + I 10.0 / 180 + COS 50.0 * 500.0 + I 10.0 / SIN 50.0 * 100.0 + I 10.0 / COS 50.0 * 500.0 + I g b DRAWCOLOR DRAWLINE LOOP .V");
  cout << code << endl;
  chunks = tokenize(code, chunks);
  evaluate(chunks);
  memset(code, 0, 256);
  chunks.clear();

#define DEBUG

  strcpy(code, "CLEAR 10 BEGIN DUP 60 + DUP 300 + SWAP DUP DUP 3 / RANDOM RANDOM RANDOM .DT\" Hello_World!\" .S 24 + DUP 180 < WHILE DROP");
  cout << code << endl;
  chunks = tokenize(code, chunks);
  evaluate(chunks);
  memset(code, 0, 256);
  chunks.clear();

  SDL_RenderPresent(renderer);

  while (!quit) {
    // Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      // User requests quit
      if (e.type == SDL_EVENT_QUIT) {
        quit = 1;
      }
    }
  }
  // Clean up
  //    SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
