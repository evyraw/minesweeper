#include "cell.h"

Cell::Cell(int x, int y) : x_(x), y_(y) {}

int Cell::get_x() const { return x_; }
int Cell::get_y() const { return y_; }

bool Cell::is_revealed() const { return revealed_; }

bool Cell::is_mine() const { return mine_; }

FlagState Cell::get_flag_state() const { return flag_state_; }

void Cell::reveal() { revealed_ = true; }

void Cell::set_mine() { mine_ = true; }

void Cell::cycle_flag() {
  switch (flag_state_) {
  case FlagState::NoFlag:
    flag_state_ = FlagState::Flag;
    break;
  case FlagState::Flag:
    flag_state_ = FlagState::Question;
    break;
  case FlagState::Question:
    flag_state_ = FlagState::NoFlag;
    break;
  }
}