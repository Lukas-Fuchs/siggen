#pragma once

#include <string>

#include "global.h"

struct Widget {
  std::string title = "##default";
  bool show = true;
  float x, y, w, h;

  virtual void paint() const {}
};