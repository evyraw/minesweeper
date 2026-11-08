#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>

#include "grid.h"

struct SDLState {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  int window_width = 1000;
  int window_height = 600;
  int logical_width = 0;
  int logical_height = 0;
};

const int GRID_WIDTH = 16;
const int GRID_HEIGHT = 12;
const int N_MINES = 10;
const float CELL_SIZE = 16.0f;

bool initialize(SDLState &state);
void cleanup(SDLState &state);
void render_grid(SDL_Renderer *renderer, const Grid &grid);
void render_cell(SDL_Renderer *renderer, int x_index, int y_index, bool mine);
void draw_filled_circle(SDL_Renderer *renderer, float center_x, float center_y,
                        float radius);

int main(int, char *[]) {

  // Init SDL state instance
  SDLState state;
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
        state.window_width = event.window.data1;
        state.window_height = event.window.data2;
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
    render_grid(state.renderer, grid);

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

  state.window = SDL_CreateWindow("Minesweeper", state.window_width,
                                  state.window_height, SDL_WINDOW_RESIZABLE);
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

void render_grid(SDL_Renderer *renderer, const Grid &grid) {
  const int width = grid.get_width();
  const int height = grid.get_height();

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      render_cell(renderer, x, y, grid.is_mine(x, y));
    }
  }
}

void render_cell(SDL_Renderer *renderer, int x_index, int y_index, bool mine) {
  float x = x_index * CELL_SIZE;
  float y = y_index * CELL_SIZE;

  // Border
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
  const SDL_FRect square = {x, y, CELL_SIZE, CELL_SIZE};
  SDL_RenderRect(renderer, &square);

  // Mine
  if (mine) {

    float center_x = x + CELL_SIZE / 2;
    float center_y = y + CELL_SIZE / 2;
    float radius = CELL_SIZE / 4;

    SDL_SetRenderDrawColor(renderer, 200, 20, 100, 255);
    draw_filled_circle(renderer, center_x, center_y, radius);
  }
}

void draw_filled_circle(SDL_Renderer *renderer, float center_x, float center_y,
                        float radius) {
  const int x0 = static_cast<int>(SDL_floorf(center_x - radius));
  const int x1 = static_cast<int>(SDL_ceilf(center_x + radius));
  const int y0 = static_cast<int>(SDL_floorf(center_y - radius));
  const int y1 = static_cast<int>(SDL_ceilf(center_y + radius));

  for (int py = y0; py < y1; ++py) {
    for (int px = x0; px < x1; ++px) {
      const float dx = (px + 0.5f) - center_x;
      const float dy = (py + 0.5f) - center_y;
      if (dx * dx + dy * dy <= radius * radius) {
        const SDL_FRect pixel = {static_cast<float>(px), static_cast<float>(py),
                                 1.0f, 1.0f};
        SDL_RenderFillRect(renderer, &pixel);
      }
    }
  }
}