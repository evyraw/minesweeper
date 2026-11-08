#include <stdexcept>

#include "grid.h"

Grid::Grid(int nCol, int nRow, int nMine)
    : nCol(nCol), nRow(nRow), nMine(nMine) {
  createGrid();
}

int Grid::getNCol() const { return nCol; }

int Grid::getNRow() const { return nRow; }

int Grid::getNMine() const { return nMine; }

Cell &Grid::at(int x, int y) {
  if (x < 0 || x >= nCol || y < 0 || y >= nRow) {
    throw std::out_of_range("Grid::at: coordinates out of range");
  }
  return cells[index(x, y)];
}
const Cell &Grid::at(int x, int y) const {
  if (x < 0 || x >= nCol || y < 0 || y >= nRow) {
    throw std::out_of_range("Grid::at: coordinates out of range");
  }
  return cells[index(x, y)];
}

void Grid::createGrid() {
  cells.reserve(nCol * nRow); // Reserves space in memory
  for (int y = 0; y < nRow; y++) {
    for (int x = 0; x < nCol; x++) {
      cells.emplace_back(x, y);
    }
  }
}

int Grid::index(int x, int y) const { return y * nCol + x; }