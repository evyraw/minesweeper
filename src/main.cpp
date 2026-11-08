#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "grid.h"

struct SDLState {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  int width = 800;
  int height = 600;
  int logical_width = 0;
  int logical_height = 0;
};

const int GRID_WIDTH = 16;
const int GRID_HEIGHT = 12;
const int N_MINES = 3;
const float CELL_SIZE = 16.0f;

bool initialize(SDLState &state);
void cleanup(SDLState &state);
void render_grid(const Grid &grid, SDL_Renderer *renderer);

int main(int argc, char *argv[]) {

  // Init SDL state instance
  SDLState state;
  state.width = 800;
  state.height = 600;
  state.logical_width = static_cast<int>(GRID_WIDTH * CELL_SIZE);
  state.logical_height = static_cast<int>(GRID_HEIGHT * CELL_SIZE);

  // Init SDL, exit if not sucessful
  if (!initialize(state)) {
    return 1;
  }

  // Init game
  Grid grid(GRID_WIDTH, GRID_HEIGHT, N_MINES);

  // uint64_t prevTime = SDL_GetTicks();

  // Game loop
  bool running = true;
  while (running) {

    // Delta time, in s
    // uint64_t nowTime = SDL_GetTicks();
    // float deltaTime = (nowTime - prevTime) / 1000.0f;
    // prevTime = nowTime;

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
    // Clear screen (black)
    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state.renderer);

    SDL_SetRenderDrawColor(state.renderer, 20, 20, 100, 255);
    SDL_FRect game_area = {0.0f, 0.0f, static_cast<float>(state.logical_width),
                           static_cast<float>(state.logical_height)};
    SDL_RenderFillRect(state.renderer, &game_area);

    // exemples
    // SDL_SetRenderDrawColor(state.renderer, 200, 200, 220, 255);
    // SDL_FRect square = {0.0f, 0.0f, 40.0f, 40.0f}; // x, y, w, h
    // SDL_RenderFillRect(state.renderer, &square);

    // SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
    // SDL_FRect outline = {200.0f, 50.0f, 40.0f, 40.0f};
    // SDL_RenderRect(state.renderer, &outline);

    // Render cells
    render_grid(grid, state.renderer);

    // Swap buffers and present
    SDL_RenderPresent(state.renderer);
  }

  // Clean quit SDL
  cleanup(state);
  return 0;
}

bool initialize(SDLState &state) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(),
                             nullptr);
    return false;
  }

  state.window = SDL_CreateWindow("Minesweeper", state.width, state.height,
                                  SDL_WINDOW_RESIZABLE);
  if (!state.window) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(),
                             nullptr);
    SDL_Quit();
    return false;
  }

  state.renderer = SDL_CreateRenderer(state.window, nullptr);
  if (!state.renderer) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(),
                             nullptr);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
    return false;
  }

  SDL_SetRenderLogicalPresentation(state.renderer, state.logical_width,
                                   state.logical_height,
                                   SDL_LOGICAL_PRESENTATION_LETTERBOX);
  return true;
}

void cleanup(SDLState &state) {

  // Destroy renderer
  SDL_DestroyRenderer(state.renderer);

  // Destroy window
  SDL_DestroyWindow(state.window);

  // Clean quit SDL
  SDL_Quit();
}

void render_grid(const Grid &grid, SDL_Renderer *renderer) {
  const int width = grid.get_width();
  const int height = grid.get_height();

  SDL_SetRenderDrawColor(renderer, 20, 200, 100, 255);

  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {

      float x = i * CELL_SIZE;
      float y = i * CELL_SIZE;
      const SDL_FRect square = {x, y, CELL_SIZE, CELL_SIZE};
      SDL_RenderRect(renderer, &square);
    }
  }
}