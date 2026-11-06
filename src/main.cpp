#include <SDL3/SDL.h>

int main() {
  //   if (!SDL_Init(SDL_INIT_VIDEO)) {
  //     SDL_Log("Init failed : %s", SDL_GetError());
  //     return 1;
  //   }

  //   SDL_Window *window = SDL_CreateWindow("Minesweeper", 640, 480, 0);
  //   if (!window) {
  //     SDL_Log("Window init failed: %s", SDL_GetError());
  //     SDL_Quit();
  //     return 1;
  //   }

  //   SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  //   if (!renderer) {
  //     SDL_Log("Renederer init failed : %s", SDL_GetError());
  //     SDL_DestroyWindow(window);
  //     SDL_Quit();
  //     return 1;
  //   }

  //   bool running = true;
  //   while (running) {
  //     SDL_Event event;
  //     while (SDL_PollEvent(&event)) {
  //       if (event.type == SDL_EVENT_QUIT) {
  //         running = false;
  //       }
  //     }

  //     SDL_SetRenderDrawColor(renderer, 40, 40, 60, 255);
  //     SDL_RenderClear(renderer);
  //     SDL_RenderPresent(renderer);

  //     SDL_Delay(16);
  //   }

  //   SDL_DestroyRenderer(renderer);
  //   SDL_DestroyWindow(window);
  //   SDL_Quit();
  return 0;
}