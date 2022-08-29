#ifndef MODULE_INCLUDED
#define MODULE_INCLUDED

#include <string>

#include "def.h"
#include "global.h"
#include "imgui.h"

#include <vector>
#include <iostream>
#include <tuple>

struct Port {
  void put(const std::vector<complex>& input) { state = input; }
  const std::vector<complex>& get() { return state; }

  std::tuple<size_t, size_t> getDims() { return {rows, cols}; }

  Port(std::string name, size_t rows, size_t cols) {
    id = global::getNextID();
    this->name = name;
    this->rows = rows;
    this->cols = cols;
    state = std::vector<complex>(rows * cols);
  }

  size_t id;
  std::string name;

  size_t connection_count = 0;
  mutable bool visible = true;

private:
  std::vector<complex> state;
  size_t rows, cols;
};

struct Module {
  enum class Type { Generator, FFT, Unknown };

  Type type;
  size_t id;

  std::vector<Port> inputs;
  std::vector<Port> outputs;
  ImVec2 preferred_dims{150.0f, 100.0f};

  Module() { id = global::getNextID(); }

  virtual void calculate(){};
  virtual void paint() const {};
};

#endif