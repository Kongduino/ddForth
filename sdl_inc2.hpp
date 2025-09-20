  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO) || !TTF_Init()) {
    SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
  // Create a window
  window = SDL_CreateWindow("ddForth SDL", 800, 600, SDL_WINDOW_RESIZABLE);
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
  evaluate(chunks);
  memset(code, 0, 256);
  chunks.clear();
  vector<string> thisBlock = loadFile((char *)"tests/t0.fs");
  if (thisBlock.size() == 0) {
    cerr << "Unable to open file!" << endl;
    return -1;
  }
  for (vector<string>::iterator it = thisBlock.begin(); it != thisBlock.end(); ++it) {
    string line = *it;
    strcpy(code, line.c_str());
    chunks = tokenize(code, chunks);
    cout << "Read: " << line << " chunks: " << chunks.size() << endl;
  }
  evaluate(chunks);
  memset(code, 0, 256);
  chunks.clear();

  SDL_RenderPresent(renderer);
//   SDL_Surface *surface = SDL_GetWindowSurface(window);
//   SDL_LockSurface(surface);
//   Uint32* pixel_ptr = (Uint32*)surface->pixels;
//   int x=10, y = 10;
//   Uint32 pixel_value = pixel_ptr[(y * surface->pitch / 4) + x];
//   // Assumes 32-bit pixels and pitch is a multiple of 4 bytes
//   Uint8 r, g, b, a;
//   SDL_GetRGB(pixel_value, (const SDL_PixelFormatDetails *)&surface->format, NULL, &r, &g, &b);
//     xxxxxx = snprintf((char *)msg, 255, "r: %d, g: %d, b: %d\n", r,g,b);
//   cout << msg;
//   SDL_UnlockSurface(surface);

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
