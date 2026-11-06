#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_video.h>

void cleanup(SDL_Window *window);

int main(int argc, char *argv[]) {

  // Init SDL video sub system
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    // Error message if SDL3 init failed
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error initializing SDL3", nullptr);
    return 1;
  }

  // Create Window
  int width = 800;
  int height = 400;
  // Pointer to SDL window object
  SDL_Window *window = SDL_CreateWindow("Minesweeper", width, height, 0);

  // Check if window open, quit with error message if not
  if (!window) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error creating window", window);
    cleanup(window);
    return 1;
  }

  // Rendering to show window, not yet in tuto
  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    SDL_Log("Création du renderer échouée : %s", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Game loop
  bool running = true;
  while (running) {

    // Handle events
    SDL_Event event{0};
    while (SDL_PollEvent(&event)) {

      // Close window event
      switch (event.type) {
      case SDL_EVENT_QUIT: {
        running = false;
        break;
      }
      }
    }

    // Rendering to show window, not yet in tuto
    SDL_SetRenderDrawColor(renderer, 40, 40, 60, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  // Clean quit SDL
  cleanup(window);
  return 0;
}

void cleanup(SDL_Window *window) {
  // Close window
  SDL_DestroyWindow(window);

  // Clean quit SDL
  SDL_Quit();
}