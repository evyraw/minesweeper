#pragma once

enum class FlagState { NoFlag, Flag, Question };

class Cell {
public:
  Cell(int x, int y);

  // Accessors
  int get_x() const;
  int get_y() const;
  bool is_revealed() const;
  bool is_mine() const;
  FlagState get_flag_state() const;

  // Mutators
  void reveal();
  void set_mine();
  void cycle_flag();

private:
  int x_;
  int y_;

  bool mine_ = false;
  bool revealed_ = false;

  FlagState flag_state_ = FlagState::NoFlag;
};