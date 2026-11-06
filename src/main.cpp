#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

struct SDLState {
  SDL_Window *window;
  SDL_Renderer *renderer;
};

void cleanup(SDLState &state);

int main(int argc, char *argv[]) {

  // Init SDL state instance
  SDLState state;

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
  state.window = SDL_CreateWindow("Minesweeper", width, height, 0);
  // Check if window open, quit with error message if not
  if (!state.window) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error creating window", state.window);
    cleanup(state);
    return 1;
  }

  // Create renderer
  // Pointer to SDL renderer
  state.renderer = SDL_CreateRenderer(state.window, nullptr);
  // Check if renderer init, quit with error if not
  if (!state.renderer) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error creating renderer", state.window);
    cleanup(state);
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

    // Perform drawing commands
    // Clear screen (pwhite)
    SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
    SDL_RenderClear(state.renderer);

    // Swap buffers and present
    SDL_RenderPresent(state.renderer);
  }

  // Clean quit SDL
  cleanup(state);
  return 0;
}

void cleanup(SDLState &state) {

  // Destroy renderer
  SDL_DestroyRenderer(state.renderer);

  // Destroy window
  SDL_DestroyWindow(state.window);

  // Clean quit SDL
  SDL_Quit();
}