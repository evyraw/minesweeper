#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

struct SDLState {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int width, height, logW, logH;
};

struct GameParams {
  int sizeX;
  int sizeY;
};

const int CELL_SIZE = 16;

bool initialize(SDLState &state);
void cleanup(SDLState &state);

int main(int argc, char *argv[]) {

  // Game params
  GameParams game;
  game.sizeX = 32;
  game.sizeY = 16;

  // Init SDL state instance
  SDLState state;
  state.width = 800;
  state.height = 600;
  state.logW = game.sizeX * CELL_SIZE;
  state.logH = game.sizeY * CELL_SIZE;

  // Init SDL, exit if not sucessful
  if (!initialize(state)) {
    return 1;
  };

  uint64_t prevTime = SDL_GetTicks();

  // Game loop
  bool running = true;
  while (running) {

    // Delta time, in s
    uint64_t nowTime = SDL_GetTicks();
    float deltaTime = nowTime - prevTime / 1000.0f;
    prevTime = nowTime;

    // Handle events
    SDL_Event event{0};
    while (SDL_PollEvent(&event)) {

      // Close window event
      switch (event.type) {
      case SDL_EVENT_QUIT: {
        running = false;
        break;
      }
      case SDL_EVENT_WINDOW_RESIZED: {
        state.width = event.window.data1;
        state.height = event.window.data2;
        break;
      }
      }
    }

    // Perform drawing commands
    // Clear screen (pwhite)
    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);

    SDL_SetRenderDrawColor(state.renderer, 20, 20, 100, 255);
    SDL_FRect gameArea = {0.0f, 0.0f, static_cast<float>(state.logW),
                          static_cast<float>(state.logH)};
    SDL_RenderFillRect(state.renderer, &gameArea);

    // Swap buffers and present
    SDL_RenderPresent(state.renderer);
  }

  // Clean quit SDL
  cleanup(state);
  return 0;
}

bool initialize(SDLState &state) {

  bool initSuccess = true;

  // Init SDL video sub system
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    // Error message if SDL3 init failed
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error initializing SDL3", nullptr);
    initSuccess = false;
  }

  // Create Window
  // Pointer to SDL window object
  state.window = SDL_CreateWindow("Minesweeper", state.width, state.height,
                                  SDL_WINDOW_RESIZABLE);
  // Check if window open, quit with error message if not
  if (!state.window) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error creating window", state.window);
    cleanup(state);
    initSuccess = false;
  }

  // Create renderer
  // Pointer to SDL renderer
  state.renderer = SDL_CreateRenderer(state.window, nullptr);
  // Check if renderer init, quit with error if not
  if (!state.renderer) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error",
                             "Error creating renderer", state.window);
    cleanup(state);
    initSuccess = false;
  }

  // Configure presentation
  SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);

  return initSuccess;
}

void cleanup(SDLState &state) {

  // Destroy renderer
  SDL_DestroyRenderer(state.renderer);

  // Destroy window
  SDL_DestroyWindow(state.window);

  // Clean quit SDL
  SDL_Quit();
}