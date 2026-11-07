#include "cell.h"

Cell::Cell(int x, int y)
    : x(x), y(y), mine(false), revealed(false), flagState(FlagState::None) {}

void Cell::reveal() { revealed = true; }

void Cell::setMine() { mine = true; }

void Cell::cycleFlag() {
  switch (flagState) {
  case FlagState::None:
    flagState = FlagState::Flag;
    break;
  case FlagState::Flag:
    flagState = FlagState::Question;
    break;
  case FlagState::Question:
    flagState = FlagState::None;
    break;
  }
}

bool Cell::isRevealed() const { return revealed; }

bool Cell::isMine() const { return mine; }

FlagState Cell::getFlagState() const { return flagState; }