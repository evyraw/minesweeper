#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>

#include "grid.h"

Grid::Grid(int width, int height, int n_mines)
    : width_(width), height_(height), n_mines_(n_mines) {
  create_grid();
  place_mines();
}

int Grid::get_width() const { return width_; }

int Grid::get_height() const { return height_; }

int Grid::get_n_mines() const { return n_mines_; }

Cell &Grid::at(int x, int y) {
  if (!in_bounds(x, y)) {
    throw std::out_of_range("Grid::at: coordinates out of range");
  }
  return cells_[index(x, y)];
}
const Cell &Grid::at(int x, int y) const {
  if (!in_bounds(x, y)) {
    throw std::out_of_range("Grid::at: coordinates out of range");
  }
  return cells_[index(x, y)];
}

// Create grid of cells
void Grid::create_grid() {
  cells_.reserve(width_ * height_); // Reserves space in memory
  for (int y = 0; y < height_; y++) {
    for (int x = 0; x < width_; x++) {
      cells_.emplace_back(x, y);
    }
  }
}

// Assigne cells with mine
void Grid::place_mines() {

  // Number of cells
  const int n_cells = width_ * height_;

  if (n_mines_ >= n_cells) {
    throw std::invalid_argument("Grid::place_mines: too many mines");
  }

  // Vector of indices
  std::vector<int> indices(n_cells); // Create vector
  std::iota(indices.begin(), indices.end(),
            0); // Fill vector with value from 0 to n_mines-1

  // Random generator
  std::random_device rd;
  std::mt19937 rng(rd());

  // Shuffle indices list
  std::shuffle(indices.begin(), indices.end(), rng);
}

// transform (x, y) coord to index
int Grid::index(int x, int y) const { return y * width_ + x; }

// Check if coord in bound
bool Grid::in_bounds(int x, int y) const {
  return x >= 0 && x < width_ && y >= 0 && y < height_;
}