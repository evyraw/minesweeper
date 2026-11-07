#include "grid.h"

Grid::Grid(int nCol, int nRow, int nMine)
    : nCol(nCol), nRow(nRow), nMine(nMine) {}

int Grid::getNCol() const { return nCol; }

int Grid::getNRow() const { return nRow; }

int Grid::getNMine() const { return nMine; }

Cell &Grid::at(int x, int y) { return cells[index(x, y)]; }
const Cell &Grid::at(int x, int y) const { return cells[index(x, y)]; }

void Grid::createGrid() {
  cells.reserve(nCol * nRow); // Reserves space in memory
  for (int x = 0; x < nRow; x++) {
    for (int y = 0; j < y; y++) {
      cells.emplace_back(x, y);
    }
  }
}

int Grid::index(int x, int y) const { return x * nCol + y; }