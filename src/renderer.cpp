#include "renderer.h"

#include <iostream>
#include <string>
#include <vector>

#include "player.h"
#include "world.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Player Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(std::vector<std::vector<World::Map::Tile>> const &grid,
                      Player const &player) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  SDL_Rect small_block;
  small_block.w = screen_width / grid_width / 2;
  small_block.h = screen_height / grid_height / 2;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 30, 30, 30, 255);
  SDL_RenderClear(sdl_renderer);

  // Render map
  for (size_t x = 0; x < grid.size(); x++) {
    for (size_t y = 0; y < grid[x].size(); y++) {
      switch (grid[x][y]) {
        case World::Map::Tile::kEmpty:
        case World::Map::Tile::kClosed:
          SDL_SetRenderDrawColor(sdl_renderer, 65, 65, 65, 255);
          block.x = x * block.w;
          block.y = y * block.h;
          SDL_RenderFillRect(sdl_renderer, &block);
          break;
        case World::Map::Tile::kObstacle:
          SDL_SetRenderDrawColor(sdl_renderer, 165, 42, 42, 255);
          block.x = x * block.w;
          block.y = y * block.h;
          SDL_RenderFillRect(sdl_renderer, &block);
          break;
        case World::Map::Tile::kFinish:
          SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 0, 255);
          block.x = x * block.w;
          block.y = y * block.h;
          SDL_RenderFillRect(sdl_renderer, &block);
          break;
        case World::Map::Tile::kStart:
          SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 255, 255);
          block.x = x * block.w;
          block.y = y * block.h;
          SDL_RenderFillRect(sdl_renderer, &block);
          break;
        default:
          SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
          block.x = x * block.w;
          block.y = y * block.h;
          SDL_RenderFillRect(sdl_renderer, &block);
          break;
      }
    }
  }

  // Render player
  auto [p_x, p_y] = player.GetPosition();
  // Add block.w / 4 to x,y position of small block to move
  // it into the center of the respective block
  small_block.x = p_x * block.w + block.w / 4;
  small_block.y = p_y * block.h + block.h / 4;
  SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 100);
  SDL_RenderFillRect(sdl_renderer, &small_block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Player Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
