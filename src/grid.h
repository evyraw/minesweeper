#pragma once

class Grid {
public:
  Grid(int nCol, int nRow, int nMine);

  int getNCol() const;
  int getNRow() const;
  int getNMine() const;

private:
  int nCol;
  int nRow;
  int nMine;
};