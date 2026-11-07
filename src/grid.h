#pragma once

#include <vector>

#include "cell.h"

class Grid {
public:
  Grid(int nCol, int nRow, int nMine);

  int getNCol() const;
  int getNRow() const;
  int getNMine() const;

  Cell &at(int x, int y);
  const Cell &at(int x, int y) const;

private:
  int nCol;
  int nRow;
  int nMine;
  std::vector<Cell> cells;

  void createGrid();

  int index(int x, int y) const;
};