#pragma once

#include <vector>

#include "cell.h"

class Grid {
public:
  Grid(int width, int height, int n_mines);

  int get_width() const;
  int get_height() const;
  int get_n_mines() const;

  Cell &at(int x, int y);
  const Cell &at(int x, int y) const;

private:
  int width;
  int height;
  int n_mines;
  std::vector<Cell> cells;

  void create_grid();
  void place_mines();

  int index(int x, int y) const;

  bool in_bounds(int x, int y) const;
};