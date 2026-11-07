#pragma once

enum class FlagState { None, Flag, Question };

class Cell {
public:
  Cell(int x, int y);

  void reveal();
  void setMine();
  void cycleFlag();

  bool isRevealed() const;
  bool isMine() const;
  FlagState getFlagState() const;

private:
  int x; // x coordinate of the cell in the grid
  int y; // y coordinate of the cell in the grid

  bool mine;
  bool revealed;

  FlagState flagState;
};