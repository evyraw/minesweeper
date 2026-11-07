#include "grid.h"

Grid::Grid(int nCol, int nRow, int nMine)
    : nCol(nCol), nRow(nRow), nMine(nMine) {}

int Grid::getNCol() const { return nCol; }

int Grid::getNRow() const { return nRow; }

int Grid::getNMine() const { return nMine; }